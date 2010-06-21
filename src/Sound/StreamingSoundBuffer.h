/** 
 * Project Vector
 * Soundbuffer für stream-Daten
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _STREAMINGSOUNDBUFFER_H
#define _STREAMINGSOUNDBUFFER_H

#include "global.h"
#include "SoundBuffer.h"

namespace pv {
namespace sound {

	//! Soundbuffer für stream-Daten
	class StreamingSoundBuffer : public SoundBuffer
	{
		friend class StreamingAudioSource;
		friend class SoundEmitter;
		friend class SoundDevice;

	protected:

		//! Erzeugt eine neue Instanz des Objektes
		StreamingSoundBuffer(SoundDevice* device, irr::u32 bufferCount = 4, irr::u32 bufferSize = 4*8192);

	public:

		// Destruktor
		virtual ~StreamingSoundBuffer(void);

		//! Updated den Streaming Audio-Puffer
		void updateStreamingAudio() const;

		//! Ermittelt die verknüpfte Audioquelle
		inline class StreamingAudioSource* getAttachedStreamingSource() const { return attachedStreamingSource; }

		//! Ermittelt die Größe eines Audiopuffer-Frames
		inline irr::u32 getBufferSize() const { return streamingBufferSize; }

		//! Entfernt die Audioquelle
		void detachStreamingSource();

	private:

		//! Setzt den Emitter
		inline void attachEmitter(class SoundEmitter* emitter) { 
			detachEmitter();
			attachedEmitter = emitter; 
		}

		//! Entfernt den Emitter
		void detachEmitter(); // TODO: Bestehende Buffer unqueuen!

		//! Bezieht den verknüpften Emitter
		inline SoundEmitter* getAttachedEmitter() const { return attachedEmitter; }

		//! Un-queuet die Puffer
		void unqueueBufferFromEmitter();

	private:

		//! Die verknüpfte Streaming-Quelle
		StreamingAudioSource* attachedStreamingSource;

		//! Die Größe des Audiopuffers
		irr::u32 streamingBufferSize;

		//! Der verknüpfte Emitter
		SoundEmitter* attachedEmitter;
	};

}}

#endif
