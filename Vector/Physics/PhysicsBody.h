/** 
 * Project Vector
 * Physikkörper
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSBODY_H
#define _PHYSICSBODY_H

#include "global.h"
#include "PhysicsMotionState.h"

namespace bullet {
#include <btBulletDynamicsCommon.h>
}

namespace pv {
namespace physics {

	//! Physikkörper
	class PhysicsBody
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsBody();

		//! Destruktor
		virtual ~PhysicsBody(void);

	private:

		//! Der Bewegungszustand
		PhysicsMotionState* motionState;
	};

}}

#endif
