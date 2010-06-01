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

	// Vorwärtsdeklaration der benötigten Klassen
	class SoundDeviceManager;

	//! Sound Device
	class SoundDevice
	{
		friend class SoundDeviceManager;

	private:
		//! Erzeugt eine neue Instanz des Objektes
		SoundDevice();

	public:

		// Destruktor
		virtual ~SoundDevice(void);

		//! Ermittelt die Device-ID
		inline irr::u32 getDeviceId() const { return deviceId; }

		//! Ermittelt die Device-ID
		inline SoundDeviceManager* getDeviceManager() const { return parent; }

	private:

		//! Ermittelt die Device-ID
		inline void setDeviceId(SoundDeviceManager* manager, irr::u32 id) { deviceId = id; parent = manager; }

	private:

		//! Die Device-ID
		irr::u32 deviceId;

		//! Der beheimatende Manager
		SoundDeviceManager* parent;
	};

}}

#endif
