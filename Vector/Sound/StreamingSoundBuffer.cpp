/** 
 * Project Vector
 * Soundbuffer für stream-Daten
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "StreamingSoundBuffer.h"
#include "StreamingAudioSource.h"

namespace pv {
namespace sound {

	StreamingSoundBuffer::StreamingSoundBuffer(SoundDevice* device, irr::u32 bufferCount, irr::u32 bufferSize)
		: SoundBuffer(device, bufferCount), streamingBufferSize(bufferSize)
	{
		ASSERT(bufferSize);
		ASSERT(bufferCount > 1);
	}


	StreamingSoundBuffer::~StreamingSoundBuffer(void)
	{
	}

	//! Updated den Streaming Audio-Puffer
	void StreamingSoundBuffer::updateStreamingAudio() const {
		ASSERT(attachedStreamingSource);
		attachedStreamingSource->updateStreamingAudio();
	}

}}