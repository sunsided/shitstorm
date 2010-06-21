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
#include "SingleSoundBuffer.h"
#include "StreamingSoundBuffer.h"
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
		friend class SoundEmitter;
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
		inline SoundContext* setActiveContext(SoundContext* context) { return setActiveContext(context, true);	}

		//! Liefert den aktuellen Kontext
		inline SoundContext* getActiveContext() const { return activeContext; }

		//! Erzeugt eine SoundBuffer-Instanz
		SoundBuffer* createBufferEx(irr::u32 size);

		//! Erzeugt eine SoundBuffer-Instanz
		inline SingleSoundBuffer* createBuffer() { return createSingleBuffer(); }

		//! Erzeugt eine SingleSoundBuffer-Instanz
		SingleSoundBuffer* createSingleBuffer();

		//! Erzeugt eine StreamingSoundBuffer-Instanz
		StreamingSoundBuffer* createStreamingBuffer(irr::u32 size = 4, irr::u32 bufferSize = 4*8192);

		//! Bezieht einen Puffer
		inline SoundBuffer* getBuffer(irr::u32 bufferId = 0) { return bufferManager[bufferId]; }

		//! Ermittelt, ob eine Extension mit dem gegebenen Namen existiert
		ALCboolean isExtensionPresent(char* extension);

		//! Ermittelt, ob ein Kontext dieses Devices aktiv ist
		bool isActiveDevice() const;

		//! Operator zum Beziehen des OpenAL-Devices
		inline operator ALCdevice*() const { return openAlDevice; }

		//! Operator zum Beziehen des OpenAL-Kontextes
		inline operator ALCcontext*() const { return (ALCcontext*)getActiveContext(); }

		//! Liefert die Anzahl der erzeugten Puffer
		inline irr::u32 getBufferCount() { return bufferManager.count(); }

		//! Liefert die Anzahl der erzeugten Kontexte
		inline irr::u32 getContextCount() { return contextManager.count(); }

		//! Updated alle Streaming Audio-Puffer
		inline void updateStreamingAudio() {
			contextManager.iterate(updateStreamingAudio, (void*)NULL);
		}

	private:

		//! Setzt einen Kontext als aktiven Kontext
		/*
		 * @param context	Der neue Kontext
		 * @param propagate	Gibt an, ob die Information an den Manager durchgereicht werden soll
		 * @returns Der zuletzt aktiv gesetzte Kontext
		 */
		SoundContext* setActiveContext(SoundContext* context, bool propagate);

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

		//! Aktualisiert alle Streaming Audio-Puffer
		inline static void updateStreamingAudio(SoundContext* context, void* unused) {
			context->updateStreamingAudio();
		}

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
