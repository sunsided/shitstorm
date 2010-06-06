/** 
 * Project Vector
 * Sound Emitter (OpenAL Source)
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundEmitter.h"
#include "SoundDevice.h"

namespace pv {
namespace sound {

	SoundEmitter::SoundEmitter(void)
		: attachedBuffer(NULL), parentContext(NULL), soundEmitterId(0), created(false), sourceId(0), bufferIsStreamingBuffer(false)
	{
		setPosition(0, 0, 0);
		setVelocity(0, 0, 0);
		setMaxGain(2.0f);
		setMinGain(0.0f);
		setReferenceDistance(1.0f);
		setMaxDistance(10.0f);
		setRelative();
		setVelocity(0, 0, 0);
		setRolloffFactor(1.0f);
		resetOrientation();
	}


	SoundEmitter::~SoundEmitter(void)
	{
		// TODO: Was passiert, wenn jemand den Emitter löscht, ohne dass er deregistriert wurde?
		detachBuffer();
	}

	//! Der zu spielende Puffer
	void SoundEmitter::attachBuffer(SingleSoundBuffer* buffer) {
		detachBuffer();

		alGetError();
		alSourcei(sourceId, AL_BUFFER, buffer->getOpenAlBuffer());
		ALenum error = alGetError();
		if (error != AL_NO_ERROR) throw error;

		attachedBuffer = buffer;
		bufferIsStreamingBuffer = false;
	}

	//! Der zu spielende Streaming-Puffer
	void SoundEmitter::attachBuffer(StreamingSoundBuffer* buffer) {
		ASSERT(buffer);
		if (buffer->getAttachedEmitter() == this) return;

		// Unseren letzten Puffer abmelden
		detachBuffer();
		
		// Den neuen Puffer von seiner alten Quelle abmelden,
		// danach bei uns anmelden
		buffer->detachEmitter();
		buffer->attachEmitter(this);

		// Registrieren
		attachedBuffer = buffer;
		bufferIsStreamingBuffer = true;
	}

	//! Entfernt den verknüpften Puffer
	void SoundEmitter::detachBuffer() {
		if (!attachedBuffer) return;
		stop();
		alSourcei(sourceId, AL_BUFFER, 0);

		// Wenn es sich um einen Streaming-Puffer handelt, müssen wir uns abmelden
		if (bufferIsStreamingBuffer) {
			StreamingSoundBuffer* buffer = static_cast<StreamingSoundBuffer*>(attachedBuffer);
			buffer->detachEmitter();
		}

		attachedBuffer = NULL;
	}

	//! Spielt den Puffer ab
	void SoundEmitter::play() const {
		if (!sourceId) return;

		alGetError();
		alSourcePlay(sourceId);
		ALenum error = alGetError();
		if (error != AL_NO_ERROR) 
			throw error;
	}

	//! Unterbricht das Abspielen
	void SoundEmitter::pause() const {
		if (!sourceId) return;
		alSourcePause(sourceId);
		ALenum error = alGetError();
		if (error != AL_NO_ERROR) 
			throw error;
	}

	//! Hält das Abspielen an
	void SoundEmitter::stop() const {
		if (!sourceId) return;
		alSourceStop(sourceId);
		ALenum error = alGetError();
	}

	//! Spult die Quelle zurück
	void SoundEmitter::rewind() const {
		if (!sourceId) return;
		alSourceRewind(sourceId);
		ALenum error = alGetError();
		if (error != AL_NO_ERROR) 
			throw error;
	}

	//! Emittelt, ob dieser Emitter gerade spielt
	bool SoundEmitter::isPlaying() const {
		
		ALenum state;
	    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
	    return (state == AL_PLAYING);
	}

	//! Emittelt, ob dieser Emitter angehalten wurde
	bool SoundEmitter::isPaused() const {

		ALenum state;
	    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
	    return (state == AL_PAUSED);
	}

	//! Emittelt den Status des Emitters
	ALenum SoundEmitter::getState() const {
		
		ALenum state;
	    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
	    return state;
	}

	//! Vernichtet den Emitter
	void SoundEmitter::destroyEmitter() {
		if (!sourceId) return;

		detachBuffer();
		alDeleteSources(1, &sourceId);
		sourceId = 0;

		// Vom Device entfernen -- Handhabt der Kontext selbst
		// if (parentContext) parentContext->removeEmitter(this);
		// parentContext = NULL;
	}

	//! Erzeugt den Emitter
	void SoundEmitter::createEmitter() {
		if (!parentContext || sourceId) return;

		// Kontext erzeugen
		alGenSources(1, &sourceId);
	}

	//! Emittelt, ob dieser Emitter in einer Schleife spielt
	bool SoundEmitter::isLooping() const {
		if (!sourceId) return false;
		ALint value;
		alGetSourcei(sourceId, AL_LOOPING, &value);
		return value == AL_TRUE;
	}

	//! Setzt, ob dieser Emitter in einer Schleife spielt
	void SoundEmitter::setLooping(bool looping) const {
		if (!sourceId) return;
		alSourcei(sourceId, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
	}

	//! Setzt die Verstärkung
	void SoundEmitter::setGain(irr::f32 gain) const {
		ASSERT(gain >= 0);
		alSourcef(sourceId, AL_GAIN, gain);
	}

	//! Ermittelt die Verstärkung
	irr::f32 SoundEmitter::getGain() const {
		irr::f32 gain;
		alGetSourcef(sourceId, AL_GAIN, &gain);
		return gain;
	}

	//! Setzt die maximale Verstärkung
	void SoundEmitter::setMaxGain(irr::f32 gain) const {
		ASSERT(gain >= 0);
		alSourcef(sourceId, AL_MAX_GAIN, gain);
	}

	//! Ermittelt die maximale Verstärkung
	irr::f32 SoundEmitter::getMaxGain() const {
		irr::f32 gain;
		alGetSourcef(sourceId, AL_MAX_GAIN, &gain);
		return gain;
	}

	//! Setzt die minimale Verstärkung
	void SoundEmitter::setMinGain(irr::f32 gain) const {
		ASSERT(gain >= 0);
		alSourcef(sourceId, AL_MIN_GAIN, gain);
	}

	//! Ermittelt die minimale Verstärkung
	irr::f32 SoundEmitter::getMinGain() const {
		irr::f32 gain;
		alGetSourcef(sourceId, AL_MIN_GAIN, &gain);
		return gain;
	}

	//! Setzt die maximale Entfernung
	void SoundEmitter::setMaxDistance(irr::f32 value) const {
		ASSERT(value >= 0);
		alSourcef(sourceId, AL_MAX_DISTANCE, value);
	}

	//! Ermittelt die maximale Entfernung
	irr::f32 SoundEmitter::getMaxDistance() const {
		irr::f32 value;
		alGetSourcef(sourceId, AL_MAX_DISTANCE, &value);
		return value;
	}

	//! Setzt die maximale Entfernung
	void SoundEmitter::setReferenceDistance(irr::f32 value) const {
		ASSERT(value >= 0);
		alSourcef(sourceId, AL_REFERENCE_DISTANCE, value);
	}

	//! Ermittelt die maximale Entfernung
	irr::f32 SoundEmitter::getReferenceDistance() const {
		irr::f32 value;
		alGetSourcef(sourceId, AL_REFERENCE_DISTANCE, &value);
		return value;
	}

	//! Setzt die Position
	void SoundEmitter::setPosition(irr::f32 x, irr::f32 y, irr::f32 z) const {
		alSource3f(sourceId, AL_POSITION, x, y, -z);
	}

	//! Ermittelt die Position
	void SoundEmitter::getPosition(irr::f32& x, irr::f32& y, irr::f32& z) const {
		alGetSource3f(sourceId, AL_POSITION, &x, &y, &z);
		z = -z;
	}

	//! Setzt die Geschwindigkeit
	void SoundEmitter::setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) const {
		alSource3f(sourceId, AL_VELOCITY, x, y, -z);
	}

	//! Ermittelt die Geschwindigkeit
	void SoundEmitter::getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) const {
		alGetSource3f(sourceId, AL_VELOCITY, &x, &y, &z);
		z = -z;
	}

	//! Setzt die Richtung zurück
	void SoundEmitter::resetOrientation() const {
		
		irr::f32 vec[6] = {0}; // Initialisiert alle Felder auf 0
		alSourcefv(sourceId, AL_ORIENTATION, vec);
	}

	//! Setzt die Richtung
	void SoundEmitter::setOrientation(irr::core::vector3df& direction) const {
		
		irr::f32 vec[3] = { direction.X, direction.Y, -direction.Z };
		alSourcefv(sourceId, AL_ORIENTATION, vec);
	}

	//! Setzt die Richtung
	void SoundEmitter::setOrientation(irr::f32 x, irr::f32 y, irr::f32 z) const {
		alSource3f(sourceId, AL_ORIENTATION, x, y, -z);
	}

	//! Ermittelt die Geschwindigkeit
	void SoundEmitter::getOrientation(irr::f32& x, irr::f32& y, irr::f32& z) const {
		alGetSource3f(sourceId, AL_ORIENTATION, &x, &y, &z);
		z = -z;
	}

	//! Setzt den Emitter auf ambiente Wiedergabe (AL_SOURCE_RELATIVE)
	void SoundEmitter::setRelative(bool isRelative) const {
		alSourcei(sourceId, AL_SOURCE_RELATIVE, isRelative ? AL_TRUE : AL_FALSE);
	}

	//! Setzt den Rolloff-Faktor
	void SoundEmitter::setRolloffFactor(irr::f32 factor) const {
		alSourcef(sourceId, AL_ROLLOFF_FACTOR, factor);
	}

}}