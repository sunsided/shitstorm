/** 
 * Project Vector
 * Soundkontext
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundContext.h"
#include "SoundDevice.h"
#include "ContextSwitchingSoundListener.h"

namespace pv {
namespace sound {

	SoundContext::SoundContext()
		: openAlContext(NULL), parentDevice(NULL), boundListener(NULL)
	{
		// Listener erzeugen
		boundListener = new ContextSwitchingSoundListener(this);
	}


	SoundContext::~SoundContext(void)
	{
		// Listener löschen
		delete boundListener;

		// Kontext killen
		destroyContext();
	}

	//! Vernichtet den Kontext
	void SoundContext::destroyContext() {
		if (openAlContext) {

			// Wenn dieser Kontext der aktive ist, aktiven Kontext abwählen
			if (isActiveContext()) unsetActiveContext();

			// Kontext vernichten
			alcDestroyContext(openAlContext);
			openAlContext = NULL;
		}
	}


	//! Erzeugt den Kontext
	void SoundContext::createContext() {
		if (!parentDevice || openAlContext) return;

		// Device holen
		ALCdevice* device = parentDevice->getOpenALDevice();

		// Kontext erzeugen
		// TODO: Attribute?
		openAlContext = alcCreateContext(device, NULL);
	}

	//! Setzt diesen Kontext als aktiven Kontext
	SoundContext* SoundContext::makeActiveContext() {
		if (!parentDevice) return NULL;
		return parentDevice->setActiveContext(this);
	}

	//! Instruiert das Device, alle Kontexte zu deaktivieren
	void SoundContext::unsetActiveContext() {
		parentDevice->setActiveContext(NULL);
	}

	//! Ermittelt, ob dieser Kontext der aktive Kontext ist
	bool SoundContext::isActiveContext() {
		if (!parentDevice) return false;
		return (parentDevice->getActiveContext() == this);
	}

	//! Bezieht das OpenAL-Device
	inline ALCdevice* SoundContext::getOpenALDevice() const {
		if (!openAlContext) return NULL;
		return alcGetContextsDevice(openAlContext);
	}

}}