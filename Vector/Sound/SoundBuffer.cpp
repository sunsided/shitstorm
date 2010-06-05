/** 
 * Project Vector
 * Soundpuffer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundBuffer.h"
#include "SoundDevice.h"

#include <al.h>

namespace pv {
namespace sound {

	SoundBuffer::SoundBuffer(SoundDevice* device, irr::u32 count)
		: parentDevice(device), bufferCount(0), buffer(NULL), bufferInstanceId(-1)
	{
		ASSERT(device);

		//  Puffer erzeugen
		createBuffers(device, count);
	}


	SoundBuffer::~SoundBuffer(void)
	{
		releaseBuffers();
	}

	//! Erzeugt die Puffer
	void SoundBuffer::createBuffers(SoundDevice* device, irr::u32 count) {
		ASSERT(device);
		
		// Alte Puffer freigeben
		releaseBuffers();

		// Neuen Parent setzen
		parentDevice = device;

		//  Puffer erzeugen
		alGetError();
		alGenBuffers(count, buffer);
		bufferCount = count;
	}

	//! Gibt die Puffer frei
	void SoundBuffer::releaseBuffers() {
		if (buffer) {
			
			// von Parent Device lösen  - Handhabt das Device selbst
			//if (parentDevice) parentDevice->removeBuffer(this);
			//parentDevice = NULL;

			// Puffer freigeben
			alGetError();
			alDeleteBuffers(bufferCount, buffer);
			buffer = NULL;
		}
	}

	//! Füllt den Puffer mit Daten
	void SoundBuffer::bufferData(irr::u32 bufferIndex, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) const {
		ASSERT(bufferIndex < bufferCount);
		ASSERT(data);

		alGetError();
		alBufferData(buffer[bufferIndex], format,data, size, freq);
		
		// Fehler auswerten galore
		switch (alGetError()) {
		case AL_NO_ERROR:
			return;
		case AL_OUT_OF_MEMORY:
			throw "Out of memory during audio buffering";
		case AL_INVALID_ENUM:
			throw "Invalid format during audio buffering";
		case AL_INVALID_VALUE:
			throw "Invalid size for the given format during audio buffering";
		}
	}

	//! Ermittelt die Bitrate des Puffers
	irr::s32 SoundBuffer::getBitrate(irr::u32 bufferIndex) {
		ASSERT(bufferIndex < bufferCount);

		ALint value;
		alGetBufferi(buffer[bufferIndex], AL_BITS, &value);
		return value;
	}

	//! Ermittelt die Frequenz des Puffers
	irr::s32 SoundBuffer::getFrequency(irr::u32 bufferIndex) {
		ASSERT(bufferIndex < bufferCount);

		ALint value;
		alGetBufferi(buffer[bufferIndex], AL_FREQUENCY, &value);
		return value;
	}

	//! Ermittelt die Anzahl der Kanäle des Puffers
	irr::s32 SoundBuffer::getChannels(irr::u32 bufferIndex) {
		ASSERT(bufferIndex < bufferCount);

		ALint value;
		alGetBufferi(buffer[bufferIndex], AL_CHANNELS, &value);
		return value;
	}

	//! Ermittelt die Größe des Puffers in Bytes
	irr::s32 SoundBuffer::getSize(irr::u32 bufferIndex) {
		ASSERT(bufferIndex < bufferCount);

		ALint value;
		alGetBufferi(buffer[bufferIndex], AL_SIZE, &value);
		return value;
	}

}}