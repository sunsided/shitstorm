/** 
 * Project Vector
 * Soundbuffer für stream-Daten
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "StreamingSoundBuffer.h"
#include "StreamingAudioSource.h"
#include "SoundEmitter.h"

namespace pv {
namespace sound {

	StreamingSoundBuffer::StreamingSoundBuffer(SoundDevice* device, irr::u32 bufferCount, irr::u32 bufferSize)
		: SoundBuffer(device, bufferCount), streamingBufferSize(bufferSize), attachedEmitter(NULL)
	{
		ASSERT(bufferSize);
		ASSERT(bufferCount > 1);
	}


	StreamingSoundBuffer::~StreamingSoundBuffer(void)
	{
		detachEmitter();
		detachStreamingSource();
	}

	//! Updated den Streaming Audio-Puffer
	void StreamingSoundBuffer::updateStreamingAudio() const {
		ASSERT(attachedStreamingSource);
		attachedStreamingSource->updateStreamingAudio();
	}

	//! Entfernt den Emitter
	void StreamingSoundBuffer::detachEmitter() {
		if (!attachedEmitter) return;

		// Quelle anhalten
		alSourceStop(attachedEmitter->getOpenALSource());

		// Puffer unqueuen
		unqueueBufferFromEmitter();

		// Emitter abmelden
		SoundEmitter *oldEmitter = attachedEmitter;
		attachedEmitter = NULL;

		// Emitter benachrichtigen
		oldEmitter->detachBuffer();
	}

	//! Un-queuet die Puffer
	void StreamingSoundBuffer::unqueueBufferFromEmitter() {
		if (!attachedEmitter) return;

		ALuint source = attachedEmitter->getOpenALSource();

		int queued;
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);    
		while(queued--)
		{
			ALuint buffer;
			alSourceUnqueueBuffers(source, 1, &buffer);
			ALenum error = alGetError();
			if (error != AL_NO_ERROR) throw error;
		}
	}

	//! Meldet sich bei der Audioquelle ab
	void StreamingSoundBuffer::detachStreamingSource() {
		if (!attachedStreamingSource) return;
		detachEmitter();
		attachedStreamingSource->detachFromStreamingBuffer();
	}

}}
