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
		void makeActiveContext();

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
	};

}}

#endif
