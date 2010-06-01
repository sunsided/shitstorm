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
public:
	//! Erzeugt eine neue Instanz des Objektes
	StreamingSoundBuffer(void);

	// Destruktor
	virtual ~StreamingSoundBuffer(void);
};

}}

#endif
