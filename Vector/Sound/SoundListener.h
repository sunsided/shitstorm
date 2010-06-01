/** 
 * Project Vector
 * Sound Listener
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDLISTENER_H
#define _SOUNDLISTENER_H

#include "global.h"
#include "SoundSpaceObject.h"

namespace pv {
namespace sound {

	//! Sound Listener
	/**
	 * Diese Klasse steuert den Listener des aktuell aktivierten Kontextes.
	 * Ist die Steuerung eines spezifischen Kontextes nötig, kann eine
	 * Instanz des @see ContextSwitchingSoundListener verwendet werden.
	 */
	class SoundListener : public SoundSpaceObject
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		SoundListener(void);

		// Destruktor
		virtual ~SoundListener(void);


		//! Setzt die Verstärkung
		virtual void setGain(irr::f32 gain);

		//! Setzt die Position
		virtual void setPosition(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Setzt die Geschwindigkeit
		virtual void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Setzt die Richtung zurück
		virtual void resetOrientation();

		//! Setzt die Richtung
		virtual void setOrientation(irr::core::vector3df& forward);

		//! Setzt die Richtung
		virtual void setOrientation(irr::core::vector3df& forward, irr::core::vector3df& up);
	};

}}

#endif
