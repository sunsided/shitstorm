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

#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {
namespace conversion {

	//! Konvertiert eine Irrlicht-Matrix in eine Bullet-Transformation
	inline static btTransform toBtTransform(const irr::core::matrix4 &matrix) {

		// http://www.irrlicht3d.de/forum/viewtopic.php?f=1&t=852
		btScalar* p = (btScalar*)matrix.pointer();
		return btTransform(
								btMatrix3x3(p[0], p[1], p[2], p[4], p[5], p[6], p[8], p[9], p[10]),
								btVector3(p[12], p[13], p[14])
							);
	}

	//! Konvertiert einen Irrlicht-Quaternion in einen Bullet-Quaternion
	inline static btQuaternion toBulletQuaternion(const irr::core::quaternion &quaternion) {
		return btQuaternion(quaternion.X, quaternion.Y, quaternion.Z, quaternion.W);
	}

	//! Konvertiert einen Irrlicht-Vektor in einen Bullet-Vektor
	inline static btVector3 toBulletVector(const irr::core::vector3df &vector) {
		return btVector3(vector.X, vector.Y, vector.Z);
	}

	//! Konvertiert einen Bullet-Vektor in einen Irrlicht-Vektor
	inline static irr::core::vector3df toIrrlichtVector(const btVector3 &vector) {
		return irr::core::vector3df(vector.getX(), vector.getY(), vector.getZ());
	}

	//! Konvertiert eine Irrlicht-Matrix 4x4 in eine Bullet-Matrix 3x3
	inline static btMatrix3x3 toBulletMatrix(const irr::core::matrix4 &matrix) {
		btScalar* p = (btScalar*)matrix.pointer();
		return btMatrix3x3(
			p[0], p[1], p[2], 
			p[4], p[5], p[6], 
			p[8], p[9], p[10]);
	}

	//! Konvertiert drei Irrlicht-Vektoren in eine Bullet-Matrix 3x3
	inline static btMatrix3x3 toBulletMatrix(const irr::core::vector3df &row1, const irr::core::vector3df &row2, const irr::core::vector3df &row3) {
		return btMatrix3x3(
			row1.X, row1.Y, row1.Z,
			row2.X, row2.Y, row2.Z,
			row3.X, row3.Y, row3.Z);
	}
		
	//! Addiert einen Irrlicht-Vektor auf einen Bullet-Vektor
	inline static btVector3& operator +(btVector3 &bulletVector, const irr::core::vector3df &vector) {
		bulletVector.m_floats[0] += vector.X;
		bulletVector.m_floats[1] += vector.Y;
		bulletVector.m_floats[2] += vector.Z;
		return bulletVector;
	}

	//! Addiert einen Bullet-Vektor auf einen Irrlicht-Vektor
	inline static irr::core::vector3df& operator +(irr::core::vector3df &vector, const btVector3 &bulletVector) {
		vector.X += bulletVector.m_floats[0];
		vector.Y += bulletVector.m_floats[1];
		vector.Z += bulletVector.m_floats[2];
		return vector;
	}

	//! Addiert einen Irrlicht-Vektor auf einen Bullet-Vektor
	inline static btVector3& operator -(btVector3 &bulletVector, const irr::core::vector3df &vector) {
		bulletVector.m_floats[0] -= vector.X;
		bulletVector.m_floats[1] -= vector.Y;
		bulletVector.m_floats[2] -= vector.Z;
		return bulletVector;
	}

	//! Addiert einen Bullet-Vektor auf einen Irrlicht-Vektor
	inline static irr::core::vector3df& operator -(irr::core::vector3df &vector, const btVector3 &bulletVector) {
		vector.X -= bulletVector.m_floats[0];
		vector.Y -= bulletVector.m_floats[1];
		vector.Z -= bulletVector.m_floats[2];
		return vector;
	}

}}}

#endif
