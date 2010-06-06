/** 
 * Project Vector
 * Sound State
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "SoundState.h"

#include <al.h>

namespace pv {
namespace sound {

	SoundState::~SoundState(void)
	{
	}

	//! Setzt den Doppler-Faktor
	void SoundState::setDopplerFactor(irr::f32 factor) const {
		alDopplerFactor(factor);
	}

	//! Setzt die Schallgeschwindigkeit
	void SoundState::setSpeedOfSound(irr::f32 speed) const {
		alSpeedOfSound(speed);
	}

	//! Setzt das Distanzmodell
	void SoundState::setDistanceModel(SoundDistanceModel model) const {
		alDistanceModel((ALenum)AL_EXPONENT_DISTANCE);
	}

}}