/** 
 * Project Vector
 * Soundpuffer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDBUFFER_H
#define _SOUNDBUFFER_H

#include "global.h"
#include <al.h>
#include <alc.h>

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der Klassen
	class SoundDevice;

	//! Soundpuffer
	class SoundBuffer
	{
		friend class SoundDevice;

	protected:

		//! Erzeugt eine neue Instanz des Objektes
		SoundBuffer(SoundDevice* device, irr::u32 bufferCount = 1);

	public:

		//! Liefert die Puffer-ID
		inline irr::u32 getSoundBufferInstanceId() const { return bufferInstanceId; }

		//! Liefert die OpenAL-Puffer
		inline ALuint* getOpenAlBuffers() const { return buffer; }

		//! Liefert den OpenAL-Puffer mit dem gegebenen Index
		inline ALuint getOpenAlBuffer(irr::u32 bufferId = 0) const {
			ASSERT(bufferId < bufferCount);
			return buffer[bufferId];
		}
		
		//! Liefert die Anzahl der Puffer
		inline irr::u32 getBufferCount() const { return bufferCount; }

		//! Füllt den Puffer mit Daten
		void bufferData(irr::u32 bufferIndex, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) const;

		//! Ermittelt die Bitrate des Puffers
		irr::s32 getBitrate(irr::u32 bufferIndex);

		//! Ermittelt die Frequenz des Puffers
		irr::s32 getFrequency(irr::u32 bufferIndex);

		//! Ermittelt die Anzahl der Kanäle des Puffers
		irr::s32 getChannels(irr::u32 bufferIndex);

		//! Ermittelt die Größe des Puffers in Bytes
		irr::s32 getSize(irr::u32 bufferIndex);

		//! Operator zum Beziehen der OpenAL-Puffer
		inline operator ALuint*() { return getOpenAlBuffers(); }

	protected:

		//! Erzeugt die Puffer
		void createBuffers(SoundDevice* device, irr::u32 bufferCount);

		//! Gibt die Puffer frei
		void releaseBuffers();

		//! Setzt die Kontext-ID
		inline void setSoundBufferInstanceId(SoundDevice* parent, irr::u32 id) { bufferInstanceId = id; parentDevice = parent; }

	public:

		// Destruktor
		virtual ~SoundBuffer(void);

	private:

		//! Die Anzahl der verwendeten Puffer
		irr::u32 bufferCount;

		//! Das besitzende Device
		SoundDevice* parentDevice;

		//! Der Audiopuffer
		ALuint* buffer;

		//! Die Puffer-ID
		irr::u32 bufferInstanceId;
	};

}}

#endif
