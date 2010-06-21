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
#include "SoundState.h"
#include "Utility/Singleton.h"

namespace pv {
namespace sound {

	//! Manager für Sound Devices
	class SoundDeviceManager : public utility::Singleton<SoundDeviceManager>
	{
		friend class SoundDevice;
		friend class utility::Singleton<SoundDeviceManager>;

	private:

		//! Erzeugt eine neue Instanz des Objektes
		SoundDeviceManager(void);

	public:

		// Destruktor
		virtual ~SoundDeviceManager(void);

		//! Erzeugt und registriert ein Sound Device
		/** Das Gerät muss danach explizit initialisiert werden. 
		*/
		SoundDevice* createDevice();

		//! Erzeugt und registriert ein Sound Device
		SoundDevice* createAndInitDevice(char* device = NULL);

		//! Entfernt ein Device
		void removeDevice(SoundDevice* device);

		//! Entfernt ein Device
		void removeDevice(irr::u32 deviceId);

		//! Bezieht ein Device
		inline SoundDevice* getDevice(irr::u32 deviceId = 0) {
			ASSERT(deviceId < soundDevices.count());
			return soundDevices[deviceId];
		}

		//! Liefert den Namen des Default-Devices
		static irr::core::stringw getDefaultDeviceName();

		//! Liefert den Namen aller Devices
		static irr::core::stringw getDeviceNames();

		//! Bezieht das aktive Device
		inline SoundDevice* getActiveDevice() const { return activeDevice; }

		//! Updated alle Streaming Audio-Puffer
		inline void updateStreamingAudio() {
			soundDevices.iterate(updateStreamingAudio, (void*)NULL);
		}

		//! Bezieht den SoundState
		inline SoundState* getState() const { return SoundState::get(); }

	private:

		//! Setzt das aktive Device
		void setActiveDevice(SoundDevice* device);

		//! Vernichtet alle Devices
		void destroyDevices();

		//! Entsorgt ein Device
		static void destroyDevice(SoundDevice* device, void* unused);

		//! Aktualisiert alle Streaming Audio-Puffer
		inline static void updateStreamingAudio(SoundDevice* device, void* unused) {
			device->updateStreamingAudio();
		}

	private:

		//! Die registrierten Sound Devices
		utility::Manager<SoundDevice> soundDevices;

		//! Das aktive Gerät
		SoundDevice* activeDevice;
	};

}}

#endif
