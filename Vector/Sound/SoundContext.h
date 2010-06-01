/** 
 * Project Vector
 * Soundkontext
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDCONTEXT_H
#define _SOUNDCONTEXT_H

#include "global.h"

namespace pv {
namespace sound {

//! Soundkontext
class SoundContext
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundContext(void);

	// Destruktor
	virtual ~SoundContext(void);
};

}}

#endif
