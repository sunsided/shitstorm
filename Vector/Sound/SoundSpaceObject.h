/** 
 * Project Vector
 * Soundobjekt im 3D-Raum
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDSPACEOBJECT_H
#define _SOUNDSPACEOBJECT_H

#include "global.h"

namespace pv {
namespace sound {

	//! Soundobjekt im 3D-Raum
	class SoundSpaceObject
	{
	protected:

		//! Erzeugt eine neue Instanz des Objektes
		SoundSpaceObject(void);

	public:

		// Destruktor
		virtual ~SoundSpaceObject(void);

		//! Setzt die Verstärkung
		virtual void setGain(irr::f32 gain) = 0;

		//! Setzt die Position
		inline void setPosition(irr::core::vector3df &origin) { setPosition(origin.X, origin.Y, origin.Z); }

		//! Setzt die Position
		virtual void setPosition(irr::f32 x, irr::f32 y, irr::f32 z) = 0;

		//! Setzt die Geschwindigkeit
		inline void setVelocity(irr::core::vector3df &veclocity) { setVelocity(veclocity.X, veclocity.Y, veclocity.Z); }

		//! Setzt die Geschwindigkeit
		virtual void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) = 0;
	};

}}

#endif
