/** 
 * Project Vector
 * Soundkontext
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundContext.h"
#include "SoundDevice.h"
#include "ContextBoundSoundListener.h"

namespace pv {
namespace sound {

	SoundContext::SoundContext()
		: openAlContext(NULL), parentDevice(NULL), boundListener(NULL), suspended(false), emitterManager(true)
	{
		// Listener erzeugen
		boundListener = new ContextBoundSoundListener(this);
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

			// Sources anhalten!
			emitterManager.iterate(destroyEmitter, (void*)NULL);
			emitterManager.clear();

			// Vom Device entfernen - Handhabt das Device selbst
			// if (parentDevice) parentDevice->removeContext(this);
			// parentDevice = NULL;

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

	//! Suspendiert den Kontext (vor process())
	void SoundContext::suspend() {
		if (!openAlContext) return;
		alcSuspendContext(openAlContext);
		suspended = true;
	}

	//! Verarbeitet den Kontext (nach suspend())
	void SoundContext::process() {
		if (!openAlContext) return;
		alcProcessContext(openAlContext);
		suspended = false;
	}


	//! Entsorgt einen Emitter
	void SoundContext::destroyEmitter(SoundEmitter* emitter, void* unused) {
		ASSERT(emitter);
		emitter->destroyEmitter();
	}

	//! Erzeugt eine SoundEmitter-Instanz
	SoundEmitter* SoundContext::createSoundEmitter() {
		// TODO: Automatisch switchen?
		if (!isActiveContext()) throw "SoundContext::createSoundEmitter() - Context must be active to create emitters!";
		
		// Puffer erzeugen
		SoundEmitter* emitter = new SoundEmitter();
		ASSERT(emitter);

		// Registrieren
		irr::u32 id = emitterManager.add(emitter);
		emitter->setEmitterId(this, id);
		emitter->createEmitter();

		return emitter;
	}

	//! Entfernt einen Emitter
	void SoundContext::removeEmitter(SoundEmitter* emitter) {
		if (!emitter) return;
		emitterManager.remove(emitter);
		emitter->setEmitterId(NULL, -1);
	}

	//! Entfernt einen Emitter
	void SoundContext::removeEmitter(irr::u32 emitterId) {
		SoundEmitter* emitter = emitterManager.remove(emitterId);
		if (emitter) emitter->setEmitterId(NULL, -1);
	}

}}