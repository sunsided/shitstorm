/** 
 * Project Vector
 * Soundkontext
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDCONTEXT_H
#define _SOUNDCONTEXT_H

#include "global.h"

#include <alc.h>

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der Klassen
	class SoundDevice;
	class ContextBoundSoundListener;

	//! Soundkontext
	class SoundContext
	{
		friend class SoundDevice;

	private:
		//! Erzeugt eine neue Instanz des Objektes
		SoundContext();

	public:

		// Destruktor
		virtual ~SoundContext(void);

		//! Ermittelt die ID dieses Kontextes
		inline irr::u32 getContextId() const { return contextId; }

		//! Ermittelt das Elterndevice
		inline SoundDevice* getParentDevice() const { return parentDevice; }

		//! Bezieht den OpenAL-Kontext
		inline ALCcontext* getOpenALContext() const { return openAlContext; }

		//! Setzt diesen Kontext als aktiven Kontext
		/*
		 * @returns Der zuletzt aktiv gesetzte Kontext
		 */
		SoundContext* makeActiveContext();

		//! Instruiert das Device, alle Kontexte zu deaktivieren
		void unsetActiveContext();

		//! Bezieht einen Listener, der immer diesen Kontext aktualisiert.
		/** Prinzipiell ist zu empfehlen, den RoamingSoundListener zu verwenden. 
		 * Dieser aktualisiert zwar "lediglich" den jeweils aktuellen Kontext,
		 * ist dafür aber auch deutlich schneller, da die Kontext-Switches entfallen.
		 */
		inline ContextBoundSoundListener* getContextSwitchingListener() { return boundListener; }

		//! Ermittelt, ob dieser Kontext der aktive Kontext ist
		bool isActiveContext();

		//! Bezieht das OpenAL-Device
		inline ALCdevice* getOpenALDevice() const;

		//! Suspendiert den Kontext (vor process())
		void suspend();

		//! Verarbeitet den Kontext (nach suspend())
		void process();

		//! Ermittelt, ob der Kontext suspendiert wurde
		inline bool isSuspended() const { return suspended; }

		//! Operator zum Beziehen des Kontextes
		inline operator ALCcontext*() const { return openAlContext; }

		//! Operator zum Beziehen des Devices
		inline operator ALCdevice*() const { return getOpenALDevice(); }

	private:

		//! Erzeugt den Kontext
		void createContext();

		//! Vernichtet den Kontext
		void destroyContext();

		//! Setzt die Kontext-ID
		inline void setContextId(SoundDevice* parent, irr::u32 id) { contextId = id; parentDevice = parent; }

	private:

		//! Das Elternelement
		SoundDevice* parentDevice;

		//! Die ID dieses Kontextes
		irr::u32 contextId;

		//! Der OpenAL-Kontext
		ALCcontext *openAlContext;

		//! Der an diesen Kontext gebundene Listener
		ContextBoundSoundListener* boundListener;

		//! Gibt an, ob der Kontext suspendiert wurde
		bool suspended;
	};

}}

#endif
