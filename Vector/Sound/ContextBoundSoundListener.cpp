/** 
 * Project Vector
 * Sound Listener, der den Kontext automatisch wechselt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#include "ContextBoundSoundListener.h"
#include "SoundContext.h"

#include <al.h>

namespace pv {
namespace sound {

	ContextBoundSoundListener::ContextBoundSoundListener(SoundContext* parent)
		:parentContext(parent)
	{
		ASSERT(parent);
	}


	ContextBoundSoundListener::~ContextBoundSoundListener(void)
	{
	}

	//! Setzt die Verstärkung
	void ContextBoundSoundListener::setGain(irr::f32 gain) {
		ASSERT(gain >= 0);

		SoundContext* previous = parentContext->makeActiveContext();
		alListenerf(AL_GAIN, gain);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Ermittelt die Verstärkung
	irr::f32 ContextBoundSoundListener::getGain() {
		irr::f32 gain;
		
		SoundContext* previous = parentContext->makeActiveContext();
		alGetListenerf(AL_GAIN, &gain);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();

		return gain;
	}

	//! Setzt die Position
	void ContextBoundSoundListener::setPosition(irr::f32 x, irr::f32 y, irr::f32 z) {
		
		SoundContext* previous = parentContext->makeActiveContext();
		alListener3f(AL_POSITION, x, y, z);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Ermittelt die Position
	void ContextBoundSoundListener::getPosition(irr::f32& x, irr::f32& y, irr::f32& z) {
		
		SoundContext* previous = parentContext->makeActiveContext();
		alGetListener3f(AL_POSITION, &x, &y, &z);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Setzt die Geschwindigkeit
	void ContextBoundSoundListener::setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) {
		
		SoundContext* previous = parentContext->makeActiveContext();
		alListener3f(AL_VELOCITY, x, y, z);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Ermittelt die Geschwindigkeit
	void ContextBoundSoundListener::getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) {
		
		SoundContext* previous = parentContext->makeActiveContext();
		alGetListener3f(AL_VELOCITY, &x, &y, &z);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Setzt die Richtung zurück
	void ContextBoundSoundListener::resetOrientation() {
		
		irr::f32 vec[6] = {0}; // Initialisiert alle Felder auf 0

		SoundContext* previous = parentContext->makeActiveContext();
		alListenerfv(AL_ORIENTATION, vec);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Setzt die Richtung
	void ContextBoundSoundListener::setOrientation(irr::core::vector3df& forward) {
		
		irr::f32 vec[6] = { forward.X, forward.Y, forward.Z, 0, 1, 0 };

		SoundContext* previous = parentContext->makeActiveContext();
		alListenerfv(AL_ORIENTATION, vec);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

	//! Setzt die Richtung
	void ContextBoundSoundListener::setOrientation(irr::core::vector3df& forward, irr::core::vector3df& up) {
		
		irr::f32 vec[6] = { forward.X, forward.Y, forward.Z, up.X, up.Y, up.Z };

		SoundContext* previous = parentContext->makeActiveContext();
		alListenerfv(AL_ORIENTATION, vec);
		if (previous) previous->makeActiveContext(); else parentContext->unsetActiveContext();
	}

}}