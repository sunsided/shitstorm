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
#include "Scripting/Bindings/SoundBindings.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration
	class RoamingSoundListener;

	//! Sound State
	class SoundState : public utility::Singleton<SoundState>
	{
		friend class utility::Singleton<SoundState>;
		friend class scripting::SoundBindings;

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

	private:

		//! Setzt das Distanzmodell
		inline void setDistanceModelU32(const irr::u32& model) const { setDistanceModel(static_cast<SoundDistanceModel>(model)); }

	public:

		//! Bezieht den Listener
		inline RoamingSoundListener* getListener() const { return RoamingSoundListener::get(); }

		//! Ruft das Init-Event auf, falls es existiert
		/* @returns true, wenn das Event aufgerufen wurde, ansonsten false. */
		bool callInitEventIfExists();
	};

}}

#endif
