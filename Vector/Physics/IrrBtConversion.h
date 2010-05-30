/** 
 * Project Vector
 * Konvertierungsfunktioen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICS_IRRBTCONVERSION_H
#define _PHYSICS_IRRBTCONVERSION_H

#include "global.h"

namespace bullet {
#include <btBulletDynamicsCommon.h>
}

namespace pv {
namespace physics {

	//! Physikkörper
	class Conversion
	{
	private:

		//! Instanzieren verhindern
		Conversion();

	public:
		//! Konvertiert eine Irrlicht-Matrix in eine Bullet-Transformation
		inline static bullet::btTransform toBtTransform(irr::core::matrix4 &matrix) {

			// http://www.irrlicht3d.de/forum/viewtopic.php?f=1&t=852
			bullet::btScalar* p = (bullet::btScalar*)matrix.pointer();
			return bullet::btTransform(
									bullet::btMatrix3x3(p[0], p[1], p[2], p[4], p[5], p[6], p[8], p[9], p[10]),
									bullet::btVector3(p[12], p[13], p[14])
								);
		}

		//! Konvertiert einen Irrlicht-Quaternion in einen Bullet-Quaternion
		inline static bullet::btQuaternion toBulletQuaternion(irr::core::quaternion &quaternion) {
			return bullet::btQuaternion(quaternion.X, quaternion.Y, quaternion.Z, quaternion.W);
		}

		//! Konvertiert einen Irrlicht-Vektor in einen Bullet-Vektor
		inline static bullet::btVector3 toBulletVector(irr::core::vector3df &vector) {
			return bullet::btVector3(vector.X, vector.Y, vector.Z);
		}

		//! Konvertiert eine Irrlicht-Matrix 4x4 in eine Bullet-Matrix 3x3
		inline static bullet::btMatrix3x3 toBulletMatrix(irr::core::matrix4 &matrix) {
			bullet::btScalar* p = (bullet::btScalar*)matrix.pointer();
			return bullet::btMatrix3x3(
				p[0], p[1], p[2], 
				p[4], p[5], p[6], 
				p[8], p[9], p[10]);
		}

		//! Konvertiert drei Irrlicht-Vektoren in eine Bullet-Matrix 3x3
		inline static bullet::btMatrix3x3 toBulletMatrix(irr::core::vector3df &row1, irr::core::vector3df &row2, irr::core::vector3df &row3) {
			return bullet::btMatrix3x3(
				row1.X, row1.Y, row1.Z,
				row2.X, row2.Y, row2.Z,
				row3.X, row3.Y, row3.Z);
		}
	};

}}

#endif
