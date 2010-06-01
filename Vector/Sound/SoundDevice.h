/** 
 * Project Vector
 * Sound Device
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDDEVICE_H
#define _SOUNDDEVICE_H

#include "global.h"

namespace pv {
namespace sound {

//! Sound Device
class SoundDevice
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundDevice(void);

	// Destruktor
	virtual ~SoundDevice(void);
};

}}

#endif
