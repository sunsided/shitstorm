/** 
 * Project Vector
 * Sound Device Manager
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "SoundDeviceManager.h"

namespace pv {
namespace sound {

	SoundDeviceManager::SoundDeviceManager(void) : soundDevices(true)
	{
	}


	SoundDeviceManager::~SoundDeviceManager(void)
	{
		soundDevices.clear(true);
	}

	//! Erzeugt und registriert ein Sound Device
	SoundDevice* SoundDeviceManager::createDevice() {
		SoundDevice* device = new SoundDevice();
		irr::u32 id = soundDevices.add(device);
		device->setDeviceId(this, id);
		return device;
	}

	//! Entfernt ein Device
	void SoundDeviceManager::removeDevice(SoundDevice* device) {
		soundDevices.remove(device);
	}

	//! Entfernt ein Device
	void SoundDeviceManager::removeDevice(irr::u32 deviceId) {
		soundDevices.remove(deviceId);
	}

}}