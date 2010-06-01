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

namespace pv {
namespace sound {

//! Soundpuffer
class SoundBuffer
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundBuffer(void);

	// Destruktor
	virtual ~SoundBuffer(void);
};

}}

#endif
