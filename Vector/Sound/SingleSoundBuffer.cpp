/** 
 * Project Vector
 * Soundpuffer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SingleSoundBuffer.h"
#include "SoundDevice.h"

#include <al.h>

namespace pv {
namespace sound {

	SingleSoundBuffer::SingleSoundBuffer(SoundDevice* device)
		: SoundBuffer(device, 1)
	{
	}


	SingleSoundBuffer::~SingleSoundBuffer(void)
	{
	}

}}