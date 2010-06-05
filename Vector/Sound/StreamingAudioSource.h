/** 
 * Project Vector
 * Audioquelle für mit Streaming-Support
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _STREAMINGAUDIOSOURCE_H
#define _STREAMINGAUDIOSOURCE_H

#include "global.h"
#include "StreamingSoundBuffer.h"

namespace pv {
namespace sound {

	//! Audioquelle
	class StreamingAudioSource
	{
	
	protected:

		//! Erzeugt eine neue Instanz des Objektes
		StreamingAudioSource(void);

	public:

		//! Destruktor
		virtual ~StreamingAudioSource(void);
		
		//! Verknüpft die Streaming-Audioquelle mit dem Streamin-Sound-Buffer
		void attachToStreamingBuffer(StreamingSoundBuffer* buffer);

		//! Ermittelt den angehängten Streaming-Puffer
		inline StreamingSoundBuffer* getAttachedStreamingBuffer() const { return attachedBuffer; }
	
		//! Initialisiert das Streaming
		bool initializeStreaming();

		//! Updated den Streaming Audio-Puffer
		void updateStreamingAudio();

		//! Beginnt mit dem Streaming von vorne
		virtual void rewindStreaming() = 0;

	protected:

		//! Streamt die Daten aus der Datei in den Puffer
		/**
		 * @param buffer	Der zu befüllende Puffer
		 * @returns			true, wenn weitere Daten vorliegen, ansonsten false
		 */
		virtual bool streamToBuffer(ALuint buffer) = 0;

	private:

		//! Der verknüpfte Puffer
		StreamingSoundBuffer* attachedBuffer;
	};

}}

#endif
