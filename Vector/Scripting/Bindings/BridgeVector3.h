/** 
 * Project Vector
 * Vektor
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _BRIDGEVECTOR3_H
#define _BRIDGEVECTOR3_H

#include "global.h"
#include "Physics/IrrBtConversion.h"

namespace pv {
namespace scripting {

	//! Manager für beliebige Typen.
	class BridgeVector3
	{
	public:

		irr::core::vector3df vector;

	public:

		//! Erzeugt eine neue Instanz der Klasse
		BridgeVector3() {}

		//! Erzeugt eine neue Instanz der Klasse
		inline BridgeVector3(irr::f32 x, irr::f32 y, irr::f32 z) 
			: vector(x, y, z)
		{}

		//! Erzeugt eine neue Instanz der Klasse
		inline BridgeVector3(irr::core::vector3df& copy) 
			: vector(copy)
		{}

		//! Erzeugt eine neue Instanz der Klasse
		inline BridgeVector3(btVector3& copy) 
			: vector(copy.x(), copy.y(), copy.z())
		{}
		
		//! Destruktor
		inline virtual ~BridgeVector3(void) {}

		//! Cast-Operator
		inline operator btVector3() const { return btVector3(vector.X, vector.Y, vector.Z); }
		
		//! Cast-Operator
		inline operator irr::core::vector3df() const { return vector; }

		/*
		//! Kopieren
		inline BridgeVector3& operator=(const btVector3& other) { vector.X = other.x(); vector.Y = other.y(); vector.Z = other.z(); return *this; }

		//! Addition
		inline BridgeVector3 operator+(const btVector3& other) { return BridgeVector3(vector.X + other.x(), vector.Y + other.y(), vector.Z + other.z()); }

		//! Addition
		inline BridgeVector3& operator+=(const btVector3& other) { vector.X += other.x(); vector.Y += other.y(); vector.Z += other.z(); return *this; }

		//! Subtraktion
		inline BridgeVector3 operator-(const btVector3& other) { return BridgeVector3(vector.X - other.x(), vector.Y - other.y(), vector.Z - other.z()); }

		//! Subtraktion
		inline BridgeVector3& operator-=(const btVector3& other) { vector.X -= other.x(); vector.Y -= other.y(); vector.Z -= other.z(); return *this; }

		//! Multiplikation
		inline BridgeVector3 operator*(const btVector3& other) { return BridgeVector3(vector.X * other.x(), vector.Y * other.y(), vector.Z * other.z()); }

		//! Multiplikation
		inline BridgeVector3& operator*=(const btVector3& other) { vector.X *= other.x(); vector.Y *= other.y(); vector.Z *= other.z(); return *this; }

		//! Division
		inline BridgeVector3 operator/(const btVector3& other) { return BridgeVector3(vector.X / other.x(), vector.Y / other.y(), vector.Z / other.z()); }

		//! Division
		inline BridgeVector3& operator/=(const btVector3& other) { vector.X /= other.x(); vector.Y /= other.y(); vector.Z /= other.z(); return *this; }

		//! Vergleich
		inline bool operator<=(const btVector3& other) const { return (btVector3)*this <= other; }

		//! Vergleich
		inline bool operator>=(const btVector3& other) const { return (btVector3)*this >= other; }

		//! Vergleich
		inline bool operator<(const btVector3& other) const { return (btVector3)*this < other; }

		//! Vergleich
		inline bool operator>(const btVector3& other) const { return (btVector3)*this > other; }

		//! Vergleich
		inline bool operator==(const btVector3& other) const { return (btVector3)*this == other; }

		//! Vergleich
		inline bool operator!=(const btVector3& other) const { return (btVector3)*this != other; }
		
		//! Punktprodukt
		inline irr::f32 dotProduct(const BridgeVector3& other) const { return vector.dotProduct(other); }

		inline BridgeVector3 crossProduct(const btVector3& p) const {
			return BridgeVector3(vector.Y * p.z() - vector.Z * p.y(), vector.Z * p.x() - vector.X * p.z(), vector.X * p.y() - vector.Y * p.x());
		}
		*/

		//! Konstruktor für Squirrel
		/*
		static int constructor_void(HSQUIRRELVM v) {
			return SqPlus::PostConstruct(v, new BridgeVector3(), release);
		}

		//! Konstruktor für Squirrel
		static int constructor_3f(irr::f32 x, irr::f32 y, irr::f32 z, HSQUIRRELVM v) {
			return SqPlus::PostConstruct(v, new BridgeVector3(x, y, z), release);
		}

		//! Destruktor für Squirrel
		SQ_DECLARE_RELEASE(BridgeVector3);
		*/

		//! Binding-Funktion
		static void scriptingBindBridgeVector();
	};

}}

#endif
