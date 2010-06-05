/** 
 * Project Vector
 * Sound Emitter (OpenAL Source)
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundEmitter.h"

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
	void SoundEmitter::play() {
		throw "Not implemented";
	}

	//! Unterbricht das Abspielen
	void SoundEmitter::pause() {
		throw "Not implemented";
	}

	//! Hält das Abspielen an
	void SoundEmitter::stop() {
		throw "Not implemented";
	}

	//! Emittelt, ob dieser Emitter gerade spielt
	bool SoundEmitter::isPlaying() {
		
		ALenum state;
	    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
	    return (state == AL_PLAYING);
	}

	//! Vernichtet den Emitter
	void SoundEmitter::destroyEmitter() {
		if (!created) return;

		detachBuffer();
		alDeleteSources(1, &sourceId);
		created = false;
	}


	//! Erzeugt den Emitter
	void SoundEmitter::createEmitter() {
		if (!parentDevice || created) return;

		// Kontext erzeugen
		alGenSources(1, &sourceId);
		created = true;
	}

}}