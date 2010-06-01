/** 
 * Project Vector
 * Sound Listener
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDLISTENER_H
#define _SOUNDLISTENER_H

#include "global.h"
#include "SoundSpaceObject.h"

namespace pv {
namespace sound {

//! Sound Listener
class SoundListener : public SoundSpaceObject
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundListener(void);

	// Destruktor
	virtual ~SoundListener(void);
};

}}

#endif
