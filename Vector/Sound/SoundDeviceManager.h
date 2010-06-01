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
#include "Utility/Manager.h"
#include "SoundDevice.h"

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

		//! Erzeugt und registriert ein Sound Device
		SoundDevice* createDevice();

		//! Entfernt ein Device
		void removeDevice(SoundDevice* device);

		//! Entfernt ein Device
		void removeDevice(irr::u32 deviceId);

		//! Bezieht ein Device
		inline SoundDevice* SoundDeviceManager::getDevice(irr::u32 deviceId = 0) {
			ASSERT(deviceId < soundDevices.count());
			return soundDevices[deviceId];
		}

	private:

		//! Die registrierten Sound Devices
		utility::Manager<SoundDevice> soundDevices;
	};

}}

#endif
