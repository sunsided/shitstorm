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
		ASSERT(context);

		irr::u32 id = contextManager.add(context);
		context->setContextId(this, id);
		context->createContext();

		// Kontext aktivieren
		if (makeActive) setActiveContext(context);

		// Und zurückgeben
		return context;
	}

	//! Erzeugt eine SoundBuffer-Instanz
	SoundBuffer* SoundDevice::createBufferEx(irr::u32 size) {

		// TODO: Automatisch switchen?
		if (!isActiveDevice()) throw "SoundDevice::createBuffer() - Device must be active to create buffers!";

		if (size <= 1) return createSingleBuffer();
		
		// Puffer erzeugen
		SoundBuffer* buffer = new SoundBuffer(this, size);
		ASSERT(buffer);

		// Registrieren
		irr::u32 id = bufferManager.add(buffer);
		buffer->setSoundBufferInstanceId(this, id);
		// buffer->createBuffers(this, size); -- Nicht nötig, macht der Konstruktor bereits!

		return buffer;
	}

	//! Erzeugt eine SingleSoundBuffer-Instanz
	SingleSoundBuffer* SoundDevice::createSingleBuffer() {
		// TODO: Automatisch switchen?
		if (!isActiveDevice()) throw "SoundDevice::createSingleBuffer() - Device must be active to create buffers!";

		SingleSoundBuffer* buffer = new SingleSoundBuffer(this);
		ASSERT(buffer);

		// Registrieren
		irr::u32 id = bufferManager.add(buffer);
		buffer->setSoundBufferInstanceId(this, id);

		return buffer;
	}

	//! Erzeugt eine StreamingSoundBuffer-Instanz
	StreamingSoundBuffer* SoundDevice::createStreamingBuffer(irr::u32 size, irr::u32 bufferSize) {
		// TODO: Automatisch switchen?
		if (!isActiveDevice()) throw "SoundDevice::createStreamingBuffer() - Device must be active to create buffers!";

		StreamingSoundBuffer* buffer = new StreamingSoundBuffer(this, size, bufferSize);
		ASSERT(buffer);

		// Registrieren
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
	SoundContext* SoundDevice::setActiveContext(SoundContext* context, bool propagate) {

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

		// Dem Manager mitteilen
		if (propagate && context != NULL) parent->setActiveDevice(this);

		// Kontext initialisieren
		if (context != NULL && !context->stateInitialized) {
			SoundState::get()->callInitEventIfExists();
			context->stateInitialized = true;
		}

		return oldContext;
	}

	//! Ermittelt, ob eine Extension mit dem gegebenen Namen existiert
	ALCboolean SoundDevice::isExtensionPresent(char* extension) {
		if (!openAlDevice) return false;
		return alcIsExtensionPresent(openAlDevice, extension);
	}

	//! Ermittelt, ob ein Kontext dieses Devices aktiv ist
	bool SoundDevice::isActiveDevice() const {
		if (!activeContext) return false;
		
		// Device des aktiven Kontexts ermitteln
		ALCdevice* device = alcGetContextsDevice(activeContext->getOpenALContext());
		return (device == openAlDevice);
	}

}}