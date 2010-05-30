/** 
 * Project Vector
 * Physikkörper-Bewegungszustand
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSMOTIONSTATE_H
#define _PHYSICSMOTIONSTATE_H

#include "global.h"
#include "IrrBtConversion.h"

namespace bullet {
#include <btBulletDynamicsCommon.h>
}

namespace pv {
namespace physics {

	//! Bewegungszustand eines Körpers
	class PhysicsMotionState : public bullet::btDefaultMotionState
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsMotionState(const bullet::btTransform& startTrans = bullet::btTransform::getIdentity(), const bullet::btTransform& centerOfMassOffset = bullet::btTransform::getIdentity()) 
			: bullet::btDefaultMotionState(startTrans, centerOfMassOffset) 
		{}

		//! Erzeugt eine neue Instanz des Objektes
		PhysicsMotionState(const irr::core::matrix4& startTrans, const irr::core::matrix4& centerOfMassOffset) 
			: bullet::btDefaultMotionState(conversion::toBtTransform(startTrans), conversion::toBtTransform(centerOfMassOffset)) 
		{}

		//! Destruktor
		virtual ~PhysicsMotionState(void);
	};

}}

#endif
