/** 
 * Project Vector
 * Aktueller Sound Listener
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _CURRENTSOUNDLISTENER_H
#define _CURRENTSOUNDLISTENER_H

#include "global.h"
#include "SoundListener.h"

namespace pv {
namespace sound {

	//! Sound Listener
	/**
	 * Diese Klasse steuert den Listener des aktuell aktivierten Kontextes.
	 * Ist die Steuerung eines spezifischen Kontextes nötig, kann eine
	 * Instanz des @see ContextSwitchingSoundListener verwendet werden.
	 */
	class CurrentSoundListener : public SoundListener
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		CurrentSoundListener(void);

		// Destruktor
		virtual ~CurrentSoundListener(void);


		//! Setzt die Verstärkung
		void setGain(irr::f32 gain);

		//! Ermittelt die Verstärkung
		irr::f32 getGain();

		//! Setzt die Position
		void setPosition(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Ermittelt die Position
		void getPosition(irr::f32& x, irr::f32& y, irr::f32& z);

		//! Setzt die Geschwindigkeit
		void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Ermittelt die Geschwindigkeit
		void getVelocity(irr::f32& x, irr::f32& y, irr::f32& z);

		//! Setzt die Richtung zurück
		void resetOrientation();

		//! Setzt die Richtung
		void setOrientation(irr::core::vector3df& forward);

		//! Setzt die Richtung
		void setOrientation(irr::core::vector3df& forward, irr::core::vector3df& up);
	};

}}

#endif
