/** 
 * Project Vector
 * Audioquelle für mit Streaming-Support
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "StreamingAudioSource.h"
#include "SoundEmitter.h"

namespace pv {
namespace sound {

	StreamingAudioSource::StreamingAudioSource(void)
		: attachedBuffer(NULL)
	{
	}


	StreamingAudioSource::~StreamingAudioSource(void)
	{
	}

	//! Updated den Streaming Audio-Puffer
	bool StreamingAudioSource::updateStreamingAudio() {
		if (!attachedBuffer) return false;

		// Quelle Beziehen
		ASSERT(attachedBuffer->getAttachedEmitter());
		ALuint source = attachedBuffer->getAttachedEmitter()->getOpenALSource();

		int processed;
		bool active = true;
 
		// Anzahl der verarbeiteten Puffer ermitteln
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

		while(processed--)
		{
			ALuint buffer;
        
			// Puffer entnehmen
			alSourceUnqueueBuffers(source, 1, &buffer);
			ALenum error = alGetError();
			if (error != AL_NO_ERROR) throw error;
 
			// Puffer neu befüllen
			active = streamToBuffer(buffer, attachedBuffer->getBufferSize());
 
			// Puffer wieder einhängen
			alSourceQueueBuffers(source, 1, &buffer);
			error = alGetError();
			if (error != AL_NO_ERROR) throw error;
		}
 
		return active;
	}


	//! Initialisiert das Streaming
	bool StreamingAudioSource::initializeStreaming() {
		ASSERT(attachedBuffer);

		// Streaming von vorne beginnen
		rewindStreaming();

		// Puffer initial füllen
		irr::u32 bufferCount = attachedBuffer->getBufferCount();
		ALuint* buffers = attachedBuffer->getOpenAlBuffers();
		ASSERT(buffers);

		for(irr::u32 b=0; b<bufferCount; ++b) {
			ALuint buffer = buffers[b];
			if(!streamToBuffer(buffer, attachedBuffer->getBufferSize())) return false;
		}

		// Alle Puffer einhängen
		ASSERT(attachedBuffer->getAttachedEmitter());
		ALuint source = attachedBuffer->getAttachedEmitter()->getOpenALSource();
		alSourceQueueBuffers(source, bufferCount, buffers);

		return true;
	}

	//! Verknüpft die Streaming-Audioquelle mit dem Streaming-Sound-Buffer
	void StreamingAudioSource::attachToStreamingBuffer(StreamingSoundBuffer* buffer) {
		detachFromStreamingBuffer();
		if (!buffer) return;

		// Verkabeln
		attachedBuffer = buffer;
		attachedBuffer->attachedStreamingSource = this;
	}

	//! Entknüpft die Audioquelle
	void StreamingAudioSource::detachFromStreamingBuffer() {
		if (attachedBuffer) {
			attachedBuffer->attachedStreamingSource = NULL;
			attachedBuffer = NULL;
		}
	}

}}