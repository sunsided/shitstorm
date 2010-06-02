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
			// von Parent Device lösen
			if (parentDevice) parentDevice->removeBuffer(this);
			parentDevice = NULL;

			// Puffer freigeben
			alGetError();
			alDeleteBuffers(bufferCount, buffer);
			buffer = NULL;
		}
	}

}}