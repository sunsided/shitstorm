/** 
 * Project Vector
 * Soundobjekt im 3D-Raum
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _PositionalAudioObject_H
#define _PositionalAudioObject_H

#include "global.h"

namespace pv {
namespace sound {

	//! Soundobjekt im 3D-Raum
	class PositionalAudioObject
	{
	protected:

		//! Erzeugt eine neue Instanz des Objektes
		PositionalAudioObject(void);

	public:

		// Destruktor
		virtual ~PositionalAudioObject(void);

		//! Setzt die Verstärkung
		virtual void setGain(irr::f32 gain) const = 0;

		//! Ermittelt die Verstärkung
		virtual irr::f32 getGain() const = 0;

		//! Setzt die Position
		inline void setPosition(irr::core::vector3df &origin) const { setPosition(origin.X, origin.Y, origin.Z); }

		//! Setzt die Position
		virtual void setPosition(irr::f32 x, irr::f32 y, irr::f32 z) const = 0;

		//! Ermittelt die Position
		inline void getPosition(irr::core::vector3df &position) const { getPosition(position.X, position.Y, position.Z); }

		//! Ermittelt die Position
		inline irr::core::vector3df getPosition() const { 
			irr::core::vector3df position;
			getPosition(position); 
			return position;
		}

		//! Ermittelt die Position
		virtual void getPosition(irr::f32& x, irr::f32& y, irr::f32& z) const = 0;

		//! Setzt die Geschwindigkeit
		inline void setVelocity(irr::core::vector3df &veclocity) const { setVelocity(veclocity.X, veclocity.Y, veclocity.Z); }

		//! Setzt die Geschwindigkeit
		virtual void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) const = 0;

		//! Ermittelt die Geschwindigkeit
		virtual void getVelocity(irr::core::vector3df &velocity) const { getVelocity(velocity.X, velocity.Y, velocity.Z); }

		//! Ermittelt die Geschwindigkeit
		virtual void getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) const = 0;

		//! Ermittelt die Geschwindigkeit
		inline irr::core::vector3df getVelocity() const { 
			irr::core::vector3df value;
			getVelocity(value); 
			return value;
		}
	};

}}

#endif
