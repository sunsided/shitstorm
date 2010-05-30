/** 
 * Project Vector
 * Physikkörper-Basisklasse
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSBODY_H
#define _PHYSICSBODY_H

#include "global.h"

namespace bullet {
#include <btBulletDynamicsCommon.h>
}

namespace pv {
namespace physics {

	//! Physikkörper
	class PhysicsBody : public bullet::btDefaultMotionState
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsBody(void) : bullet::btDefaultMotionState() {}

		//! Destruktor
		virtual ~PhysicsBody(void);
	};

}}

#endif
