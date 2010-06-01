/** 
 * Project Vector
 * Soundkontext
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "SoundContext.h"
#include "SoundDevice.h"

namespace pv {
namespace sound {

	SoundContext::SoundContext()
		: openAlContext(NULL), parentDevice(NULL)
	{
	}


	SoundContext::~SoundContext(void)
	{
		destroyContext();
	}

	//! Vernichtet den Kontext
	void SoundContext::destroyContext() {
		if (openAlContext) {

			// TODO: Wenn dieser Kontext der aktive ist, aktiven Kontext abwählen
			// TODO: Assoziierte Listener etc. killen?

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
	void SoundContext::makeActiveContext() {
		if (!parentDevice) return;
		parentDevice->setActiveContext(this);
	}

}}