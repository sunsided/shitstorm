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
#include "PositionalAudioObject.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration
	class RoamingSoundListener;

	//! Sound Listener
	/**
	 * Diese Klasse steuert den Listener des aktuell aktivierten Kontextes.
	 * Ist die Steuerung eines spezifischen Kontextes nötig, kann eine
	 * Instanz des @see ContextBoundSoundListener verwendet werden.
	 */
	class SoundListener : public PositionalAudioObject
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		SoundListener(void);

		// Destruktor
		virtual ~SoundListener(void);


		//! Setzt die Verstärkung
		virtual void setGain(irr::f32 gain) const = 0;

		//! Ermittelt die Verstärkung
		virtual irr::f32 getGain() const = 0;

		//! Setzt die Position
		virtual void setPosition(irr::f32 x, irr::f32 y, irr::f32 z) const = 0;

		//! Ermittelt die Position
		virtual void getPosition(irr::f32& x, irr::f32& y, irr::f32& z) const = 0;

		//! Setzt die Geschwindigkeit
		virtual void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) const = 0;

		//! Ermittelt die Geschwindigkeit
		virtual void getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) const = 0;

		//! Setzt die Richtung zurück
		virtual void resetOrientation() const = 0;

		//! Setzt die Richtung
		virtual void setOrientation(irr::core::vector3df& forward) const = 0;

		//! Setzt die Richtung
		virtual void setOrientation(irr::core::vector3df& forward, irr::core::vector3df& up) const = 0;

	public:
		
		//! Der aktuelle SoundListener
		const static RoamingSoundListener Current;
	};

}}

#endif
