/** 
 * Project Vector
 * Sound Device Manager
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDDEVICEMANAGER_H
#define _SOUNDDEVICEMANAGER_H

#include "global.h"

namespace pv {
namespace sound {

//! Manager für Sound Devices
class SoundDeviceManager
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundDeviceManager(void);

	// Destruktor
	virtual ~SoundDeviceManager(void);
};

}}

#endif
