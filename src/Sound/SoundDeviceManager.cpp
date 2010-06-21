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

	SoundDeviceManager::SoundDeviceManager(void) : soundDevices(true), activeDevice(NULL) {
	}


	SoundDeviceManager::~SoundDeviceManager(void) {
		destroyDevices();
	}

	//! Entsorgt ein Device
	void SoundDeviceManager::destroyDevice(SoundDevice* device, void* unused) {
		device->destroy();
	}

	//! Vernichtet alle Devices
	void SoundDeviceManager::destroyDevices() {
		soundDevices.iterate(destroyDevice, (void*)NULL);
		soundDevices.clear(true);
	}

	//! Erzeugt und registriert ein Sound Device
	SoundDevice* SoundDeviceManager::createDevice() {
		SoundDevice* device = new SoundDevice();
		irr::u32 id = soundDevices.add(device);
		device->setDeviceId(this, id);
		return device;
	}

	//! Erzeugt und registriert ein Sound Device
	SoundDevice* SoundDeviceManager::createAndInitDevice(char* deviceName) {
		SoundDevice* device = createDevice();
		device->initialize(deviceName);
		return device;
	}

	//! Entfernt ein Device
	void SoundDeviceManager::removeDevice(SoundDevice* device) {
		if (!device) return;
		soundDevices.remove(device);
		device->setDeviceId(NULL, -1);
	}

	//! Entfernt ein Device
	void SoundDeviceManager::removeDevice(irr::u32 deviceId) {
		SoundDevice* device = soundDevices.remove(deviceId);
		if (device) device->setDeviceId(NULL, -1);
	}

	//!Liefert den Namen des Default-Devices
	irr::core::stringw SoundDeviceManager::getDefaultDeviceName() {
		// TODO: Speicherleck?
		return alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	}

	//!Liefert den Namen aller Devices
	irr::core::stringw SoundDeviceManager::getDeviceNames() {
		// TODO: Speicherleck?
		return alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	}

	//! Setzt das aktive Device
	void SoundDeviceManager::setActiveDevice(SoundDevice* device) {

		// Altes Gerät abwählen
		if (activeDevice && activeDevice != device) {
			activeDevice->setActiveContext(NULL, false);
		}

		// Gerät setzen
		activeDevice = device;
	}

}}