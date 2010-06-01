/** 
 * Project Vector
 * Aktueller Sound Listener
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "CurrentSoundListener.h"

#include <al.h>

namespace pv {
namespace sound {

	CurrentSoundListener::CurrentSoundListener(void)
	{
	}


	CurrentSoundListener::~CurrentSoundListener(void)
	{
	}

	//! Setzt die Verstärkung
	void CurrentSoundListener::setGain(irr::f32 gain) {
		ASSERT(gain >= 0);
		alListenerf(AL_GAIN, gain);
	}

	//! Ermittelt die Verstärkung
	irr::f32 CurrentSoundListener::getGain() {
		irr::f32 gain;
		alGetListenerf(AL_GAIN, &gain);
		return gain;
	}

	//! Setzt die Position
	void CurrentSoundListener::setPosition(irr::f32 x, irr::f32 y, irr::f32 z) {
		alListener3f(AL_POSITION, x, y, z);
	}

	//! Ermittelt die Position
	void CurrentSoundListener::getPosition(irr::f32& x, irr::f32& y, irr::f32& z) {
		alGetListener3f(AL_POSITION, &x, &y, &z);
	}

	//! Setzt die Geschwindigkeit
	void CurrentSoundListener::setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) {
		alListener3f(AL_VELOCITY, x, y, z);
	}

	//! Ermittelt die Geschwindigkeit
	void CurrentSoundListener::getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) {
		alGetListener3f(AL_VELOCITY, &x, &y, &z);
	}

	//! Setzt die Richtung zurück
	void CurrentSoundListener::resetOrientation() {
		
		irr::f32 vec[6] = {0}; // Initialisiert alle Felder auf 0
		alListenerfv(AL_ORIENTATION, vec);
	}

	//! Setzt die Richtung
	void CurrentSoundListener::setOrientation(irr::core::vector3df& forward) {
		
		irr::f32 vec[6] = { forward.X, forward.Y, forward.Z, 0, 1, 0 };
		alListenerfv(AL_ORIENTATION, vec);
	}

	//! Setzt die Richtung
	void CurrentSoundListener::setOrientation(irr::core::vector3df& forward, irr::core::vector3df& up) {
		
		irr::f32 vec[6] = { forward.X, forward.Y, forward.Z, up.X, up.Y, up.Z };
		alListenerfv(AL_ORIENTATION, vec);
	}

}}