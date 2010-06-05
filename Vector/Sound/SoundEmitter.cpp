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
		: attachedBuffer(NULL), parentDevice(NULL), soundEmitterId(0), created(false)
	{
	}


	SoundEmitter::~SoundEmitter(void)
	{
	}

	//! Der zu spielende Puffer
	void SoundEmitter::attachBuffer(SingleSoundBuffer* buffer) {
		detachBuffer();

		alGetError();
		alSourcei(sourceId, AL_BUFFER, buffer->getOpenAlBuffer());
		ALenum error = alGetError();
		if (error != AL_NO_ERROR) throw error;

		attachedBuffer = buffer;
	}

	//! Entfernt den verknüpften Puffer
	void SoundEmitter::detachBuffer() {
		if (!attachedBuffer) return;
		stop();
		alSourcei(sourceId, AL_BUFFER, 0);
		attachedBuffer = NULL;
	}

	//! Spielt den Puffer ab
	void SoundEmitter::play() const {
		if (!sourceId) return;
		alSourcePlay(sourceId);
	}

	//! Unterbricht das Abspielen
	void SoundEmitter::pause() const {
		if (!sourceId) return;
		alSourcePause(sourceId);
	}

	//! Hält das Abspielen an
	void SoundEmitter::stop() const {
		if (!sourceId) return;
		alSourceStop(sourceId);
	}

	//! Spult die Quelle zurück
	void SoundEmitter::rewind() const {
		if (!sourceId) return;
		alSourceRewind(sourceId);
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

		// Vom Device entfernen
		if (parentDevice) parentDevice->removeEmitter(this);
		parentDevice = NULL;
	}

	//! Erzeugt den Emitter
	void SoundEmitter::createEmitter() {
		if (!parentDevice || sourceId) return;

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
	void SoundEmitter::setGain(irr::f32 gain) {
		ASSERT(gain >= 0);
		alSourcef(sourceId, AL_GAIN, gain);
	}

	//! Ermittelt die Verstärkung
	irr::f32 SoundEmitter::getGain() {
		irr::f32 gain;
		alGetSourcef(sourceId, AL_GAIN, &gain);
		return gain;
	}

	//! Setzt die Position
	void SoundEmitter::setPosition(irr::f32 x, irr::f32 y, irr::f32 z) {
		alSource3f(sourceId, AL_POSITION, x, y, z);
	}

	//! Ermittelt die Position
	void SoundEmitter::getPosition(irr::f32& x, irr::f32& y, irr::f32& z) {
		alGetSource3f(sourceId, AL_POSITION, &x, &y, &z);
	}

	//! Setzt die Geschwindigkeit
	void SoundEmitter::setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) {
		alSource3f(sourceId, AL_VELOCITY, x, y, z);
	}

	//! Ermittelt die Geschwindigkeit
	void SoundEmitter::getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) {
		alGetSource3f(sourceId, AL_VELOCITY, &x, &y, &z);
	}

	//! Setzt die Richtung zurück
	void SoundEmitter::resetOrientation() {
		
		irr::f32 vec[6] = {0}; // Initialisiert alle Felder auf 0
		alSourcefv(sourceId, AL_ORIENTATION, vec);
	}

	//! Setzt die Richtung
	void SoundEmitter::setOrientation(irr::core::vector3df& direction) {
		
		irr::f32 vec[3] = { direction.X, direction.Y, direction.Z };
		alSourcefv(sourceId, AL_ORIENTATION, vec);
	}

	//! Setzt die Richtung
	void SoundEmitter::setOrientation(irr::f32 x, irr::f32 y, irr::f32 z) {
		alSource3f(sourceId, AL_ORIENTATION, x, y, z);
	}

	//! Ermittelt die Geschwindigkeit
	void SoundEmitter::getOrientation(irr::f32& x, irr::f32& y, irr::f32& z) {
		alGetSource3f(sourceId, AL_ORIENTATION, &x, &y, &z);
	}
}}