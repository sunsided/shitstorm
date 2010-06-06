/** 
 * Project Vector
 * Sound State
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDSTATE_H
#define _SOUNDSTATE_H

#include "global.h"
#include "SoundDistanceModel.h"
#include "RoamingSoundListener.h"
#include "Utility/Singleton.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration
	class RoamingSoundListener;

	//! Sound State
	class SoundState : public utility::Singleton<SoundState>
	{
		friend class utility::Singleton<SoundState>;

	protected:

		// Destruktor
		inline SoundState(void) {}

	public:
		// Destruktor
		virtual ~SoundState(void);

		//! Setzt den Doppler-Faktor
		void setDopplerFactor(irr::f32 factor) const;

		//! Setzt die Schallgeschwindigkeit
		void setSpeedOfSound(irr::f32 speed) const;

		//! Setzt das Distanzmodell
		void setDistanceModel(SoundDistanceModel model) const;

		//! Bezieht den Listener
		inline RoamingSoundListener* getListener() const { return RoamingSoundListener::get(); }
	};

}}

#endif
