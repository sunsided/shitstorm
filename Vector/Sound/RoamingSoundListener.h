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
	 * Instanz des @see ContextBoundSoundListener verwendet werden.
	 */
	class RoamingSoundListener : public SoundListener
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		RoamingSoundListener(void);

		// Destruktor
		virtual ~RoamingSoundListener(void);


		//! Setzt die Verstärkung
		void setGain(irr::f32 gain) const;

		//! Ermittelt die Verstärkung
		irr::f32 getGain() const;

		//! Setzt die Position
		void setPosition(irr::f32 x, irr::f32 y, irr::f32 z) const;

		//! Ermittelt die Position
		void getPosition(irr::f32& x, irr::f32& y, irr::f32& z) const;

		//! Setzt die Geschwindigkeit
		void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) const;

		//! Ermittelt die Geschwindigkeit
		void getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) const;

		//! Setzt die Richtung zurück
		void resetOrientation() const;

		//! Setzt die Richtung
		void setOrientation(irr::core::vector3df& forward) const;

		//! Setzt die Richtung
		void setOrientation(irr::core::vector3df& forward, irr::core::vector3df& up) const;
	};

}}

#endif
