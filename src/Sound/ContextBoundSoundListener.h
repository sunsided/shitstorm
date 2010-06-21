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

		//! Bezieht den Elternkontext
		inline SoundContext* getContext() const { return parentContext; }

	private:

		//! Der Elternkontext
		SoundContext* parentContext;
	};

}}

#endif
