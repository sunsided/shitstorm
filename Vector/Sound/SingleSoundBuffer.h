/** 
 * Project Vector
 * Soundpuffer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SINGLESOUNDBUFFER_H
#define _SINGLESOUNDBUFFER_H

#include "global.h"
#include "SoundBuffer.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der Klassen
	class SoundDevice;

	//! Soundpuffer
	class SingleSoundBuffer : public SoundBuffer
	{
		friend class SoundDevice;

	protected:

		//! Erzeugt eine neue Instanz des Objektes
		SingleSoundBuffer(SoundDevice* device);

	public:

		//! Füllt den Puffer mit Daten
		inline void bufferData(ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) const {
			SoundBuffer::bufferData(0, format, data, size, freq);
		}

		//! Operator zum Beziehen des OpenAL-Puffers
		inline operator ALuint() { return getOpenAlBuffer(0); }

		//! Ermittelt die Bitrate des Puffers
		inline irr::s32 getBitrate() { return SoundBuffer::getBitrate(0); }

		//! Ermittelt die Frequenz des Puffers
		inline irr::s32 getFrequency() { return SoundBuffer::getFrequency(0); }

		//! Ermittelt die Anzahl der Kanäle des Puffers
		inline irr::s32 getChannels() { return SoundBuffer::getChannels(0); }

		//! Ermittelt die Größe des Puffers in Bytes
		inline irr::s32 getSize() { return SoundBuffer::getSize(0); }

	public:

		// Destruktor
		virtual ~SingleSoundBuffer(void);

	};

}}

#endif
