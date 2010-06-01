/** 
 * Project Vector
 * Sound Device
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundDevice.h"

#include <al.h>

namespace pv {
namespace sound {

	SoundDevice::SoundDevice()
		: openAlDevice(NULL), contextManager(NULL), activeContext(NULL)
	{
	}


	SoundDevice::~SoundDevice(void)
	{
		destroy();
	}

	//! Erzeugt das Device
	void SoundDevice::initialize(const char* deviceName) {
		if (openAlDevice) return;

		openAlDevice = alcOpenDevice(deviceName);
	}

	//! Entsorgt einen Kontext
	void SoundDevice::destroyContext(SoundContext* context, void* unused) {
		context->destroyContext();
	}

	//! Vernichtet das Device
	void SoundDevice::destroy() {
		if (openAlDevice) {
			
			// Kontexte löschen
			contextManager.iterate(destroyContext, (void*)NULL);
			contextManager.clear(true);

			// Aktiven Kontext abwählen
			setActiveContext(NULL);

			// OpenAL-Device vernichten
			alcCloseDevice(openAlDevice);
			openAlDevice = NULL;
		}
	}

	//! Erzeugt einen neuen Kontext
	SoundContext* SoundDevice::createContext(bool makeActive) {
		SoundContext* context = new SoundContext();
		irr::u32 id = contextManager.add(context);
		context->setContextId(this, id);

		// Kontext aktivieren
		if (makeActive) setActiveContext(context);

		// Und zurückgeben
		return context;
	}
	
	//! Entfernt einen Kontext
	void SoundDevice::removeContext(irr::u32 contextId) {
		SoundContext* context = contextManager.remove(contextId);
		if (context) context->setContextId(NULL, -1);
	}

	//! Entfernt einen Kontext
	void SoundDevice::removeContext(SoundContext* context) {
		if (!context) return;
		contextManager.remove(context);
		context->setContextId(NULL, -1);
	}

	//! Setzt einen Kontext als aktiven Kontext
	void SoundDevice::setActiveContext(SoundContext* context) {

		// OpenAL über die Kontextänderung informieren
		if (context) {
			alcMakeContextCurrent(context->getOpenALContext());
		}
		else {
			alcMakeContextCurrent(NULL);
		}

		// Kontext registrieren
		activeContext = context;
	}

}}