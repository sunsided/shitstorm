/** 
 * Project Vector
 * Sound Listener, der den Kontext automatisch wechselt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _CONTEXTSWITCHINGSOUNDLISTENER_H
#define _CONTEXTSWITCHINGSOUNDLISTENER_H

#include "global.h"
#include "SoundListener.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration
	class SoundContext;

	//! Sound Listener, der den Kontext automatisch wechselt
	class ContextBoundSoundListener : public SoundListener 
	{
		friend class SoundContext;

	private:

		//! Erzeugt eine neue Instanz des Objektes
		ContextBoundSoundListener(SoundContext* parent);

	public:

		// Destruktor
		virtual ~ContextBoundSoundListener(void);

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

	private:

		//! Der Elternkontext
		SoundContext* parentContext;
	};

}}

#endif
