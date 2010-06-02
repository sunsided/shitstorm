/** 
 * Project Vector
 * Sound Device
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundDevice.h"
#include "SoundDeviceManager.h"

#include <al.h>

namespace pv {
namespace sound {

	SoundDevice::SoundDevice()
		: openAlDevice(NULL), contextManager(true), activeContext(NULL), bufferManager(true)
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
		ASSERT(context);
		context->destroyContext();
	}

	//! Entsorgt einen Puffer
	void SoundDevice::destroyBuffer(SoundBuffer* buffer, void* unused) {
		ASSERT(buffer);
		buffer->releaseBuffers();
	}

	//! Vernichtet das Device
	void SoundDevice::destroy() {
		if (openAlDevice) {
			
			// Aktiven Kontext abwählen
			setActiveContext(NULL);

			// Kontexte löschen
			contextManager.iterate(destroyContext, (void*)NULL);
			contextManager.clear(true);
			
			// TODO: Sources anhalten!

			// Puffer löschen
			bufferManager.iterate(destroyBuffer, (void*)NULL);
			bufferManager.clear(true);

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

	//! Erzeugt eine SoundBuffer-Instanz
	SoundBuffer* SoundDevice::createBuffer(irr::u32 size) {
		SoundBuffer* buffer = new SoundBuffer(this, size);
		irr::u32 id = bufferManager.add(buffer);
		buffer->setSoundBufferInstanceId(this, id);
		return buffer;
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

	//! Entfernt einen Puffer
	void SoundDevice::removeBuffer(SoundBuffer* buffer) {
		if (!buffer) return;
		bufferManager.remove(buffer);
		buffer->setSoundBufferInstanceId(NULL, -1);
	}

	//! Entfernt einen Puffer
	void SoundDevice::removeBuffer(irr::u32 bufferId) {
		SoundContext* context = contextManager.remove(bufferId);
		if (context) context->setContextId(NULL, -1);
	}

	//! Setzt einen Kontext als aktiven Kontext
	SoundContext* SoundDevice::setActiveContext(SoundContext* context) {

		// OpenAL über die Kontextänderung informieren
		if (context) {
			alcMakeContextCurrent(context->getOpenALContext());
		}
		else {
			alcMakeContextCurrent(NULL);
		}

		// Kontext registrieren
		SoundContext* oldContext = activeContext;
		activeContext = context;
		return oldContext;
	}

	//! Detaches a Buffer from the device
	void detachBuffer(SoundBuffer* buffer) {
		throw "Not Implemented";
	}

}}