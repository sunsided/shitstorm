/** 
 * Project Vector
 * Soundbuffer für stream-Daten
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "StreamingSoundBuffer.h"

namespace pv {
namespace sound {

StreamingSoundBuffer::StreamingSoundBuffer(SoundDevice* device, irr::u32 bufferCount)
	: SoundBuffer(device, bufferCount)
{
}


StreamingSoundBuffer::~StreamingSoundBuffer(void)
{
}


}}