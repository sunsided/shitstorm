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
#include "SoundContext.h"
#include "SoundBuffer.h"
#include "Utility/Manager.h"

#include <alc.h>

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der benötigten Klassen
	class SoundDeviceManager;
	class RoamingSoundListener;
	
	//! Sound Device
	class SoundDevice
	{
		friend class SoundDeviceManager;
		friend class SoundBuffer;
		friend class SoundContext;

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
		
		//! Erzeugt das Device
		void initialize(const char* deviceName = NULL);

		//! Vernichtet das Device
		void destroy();

		//! Erzeugt einen neuen Kontext
		SoundContext* createContext(bool makeActive = true);

		//! Bezieht einen Kontext
		inline SoundContext* getContext(irr::u32 contextId = 0) { return contextManager[contextId]; }

		//! Bezieht das OpenAL-Device
		inline ALCdevice* getOpenALDevice() const { return openAlDevice; }

		//! Setzt einen Kontext als aktiven Kontext
		/*
		 * @param context	Der neue Kontext
		 * @returns Der zuletzt aktiv gesetzte Kontext
		 */
		SoundContext* setActiveContext(SoundContext* context);

		//! Liefert den aktuellen Kontext
		inline SoundContext* getActiveContext() const { return activeContext; }

		//! Erzeugt eine SoundBuffer-Instanz
		SoundBuffer* createBuffer(irr::u32 size = 1);

	private:

		//! Entfernt einen Kontext
		void removeContext(irr::u32 contextId);

		//! Entfernt einen Kontext
		void removeContext(SoundContext* context);

		//! Entfernt einen Puffer
		void removeBuffer(SoundBuffer* buffer);

		//! Entfernt einen Puffer
		void removeBuffer(irr::u32 bufferId);

		//! Setzt die Device-ID
		inline void setDeviceId(SoundDeviceManager* manager, irr::u32 id) { deviceId = id; parent = manager; }

		//! Entsorgt einen Kontext
		static void destroyContext(SoundContext* context, void* unused);

		//! Entsorgt einen Puffer
		static void destroyBuffer(SoundBuffer* buffer, void* unused);

	private:

		//! Die Device-ID
		irr::u32 deviceId;

		//! Der beheimatende Manager
		SoundDeviceManager* parent;

		//! Das OpenAL-Device
		ALCdevice* openAlDevice;

		//! Die verschiedenen Kontexte
		utility::Manager<SoundContext> contextManager;

		//! Der derzeit aktive Kontext
		SoundContext* activeContext;

		//! Der Puffer-Manager
		utility::Manager<SoundBuffer> bufferManager;
	};

}}

#endif
