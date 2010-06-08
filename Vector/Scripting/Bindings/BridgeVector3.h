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
#include "Scripting/Scripting.h"

namespace pv {
namespace scripting {

	//! Manager für beliebige Typen.
	class BridgeVector3
	{
	private:

		irr::core::vector3df vector;

	public:

		//! Erzeugt eine neue Instanz der Klasse
		inline BridgeVector3(irr::f32 x = 0, irr::f32 y = 0, irr::f32 z = 0)
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
		inline operator irr::core::vector3df&() { return vector; }

		//! Setzt alle Werte auf Null zurück
		inline void clear() { vector.X = vector.Y = vector.Z = 0; }

		//! Holt den X-Wert
		inline irr::f32 getX() const { return vector.X; }

		//! Setzt den X-Wert
		inline void setX(const irr::f32& value) { vector.X = value; }

		//! Holt den Y-Wert
		inline irr::f32 getY() const { return vector.Y; }

		//! Setzt den Y-Wert
		inline void setY(const irr::f32& value) { vector.Y = value; }

		//! Holt den Z-Wert
		inline irr::f32 getZ() const { return vector.Z; }

		//! Setzt den Z-Wert
		inline void setZ(const irr::f32& value) { vector.Z = value; }

		//! Kopieren
		inline BridgeVector3& operator=(const BridgeVector3& other) { vector.X = other.vector.X; vector.Y = other.vector.Y; vector.Z = other.vector.Z; return *this; }

		//! Addition
		inline BridgeVector3 operator+(const BridgeVector3& other) { return BridgeVector3(vector.X + other.vector.X, vector.Y + other.vector.Y, vector.Z + other.vector.Z); }

		//! Addition
		inline BridgeVector3& operator+=(const BridgeVector3& other) { vector += other.vector; return *this; }

		//! Unärer Negator
		inline BridgeVector3 getNegated() const { return BridgeVector3(-vector); }

		//! Subtraktion
		inline BridgeVector3 operator-(const BridgeVector3& other) { return BridgeVector3(vector.X - other.vector.X, vector.Y - other.vector.Y, vector.Z - other.vector.Z); }

		//! Subtraktion
		inline BridgeVector3& operator-=(const BridgeVector3& other) { vector -= other.vector; return *this; }

		/*
		//! Multiplikation
		inline BridgeVector3 operator*(const BridgeVector3& other) { return BridgeVector3(vector.X * other.vector.X, vector.Y * other.vector.Y, vector.Z * other.vector.Z); }

		//! Multiplikation
		inline BridgeVector3& operator*=(const BridgeVector3& other) { vector *= other.vector; return *this; }
		*/
		
		//! Multiplikation
		inline BridgeVector3 operator*(const irr::f32 other) { return BridgeVector3(vector.X * other, vector.Y * other, vector.Z * other); }

		//! Multiplikation
		inline BridgeVector3& operator*=(const irr::f32 other) { vector *= other; return *this; }

		/*
		//! Division
		inline BridgeVector3 operator/(const BridgeVector3& other) { return BridgeVector3(vector.X / other.vector.X, vector.Y / other.vector.Y, vector.Z / other.vector.Z); }

		//! Division
		inline BridgeVector3& operator/=(const BridgeVector3& other) { vector /= other.vector; return *this; }
		*/

		//! Multiplikation
		inline BridgeVector3 operator/(const irr::f32 other) { return BridgeVector3(vector.X / other, vector.Y / other, vector.Z / other); }

		//! Multiplikation
		inline BridgeVector3& operator/=(const irr::f32 other) { vector /= other; return *this; }

		//! Vergleich
		inline bool operator<=(const BridgeVector3& other) const { return vector <= other.vector; }

		//! Vergleich
		inline bool operator>=(const BridgeVector3& other) const { return vector >= other.vector; }

		//! Vergleich
		inline bool operator<(const BridgeVector3& other) const { return vector < other.vector; }

		//! Vergleich
		inline bool operator>(const BridgeVector3& other) const { return vector > other.vector; }

		//! Vergleich
		inline bool operator==(const BridgeVector3& other) const { return vector == other.vector; }

		//! Vergleich
		inline bool operator!=(const BridgeVector3& other) const { return vector != other.vector; }
		
		//! Punktprodukt
		inline irr::f32 dotProduct(const BridgeVector3& other) const { return vector.dotProduct(other.vector); }

		inline BridgeVector3 crossProduct(const btVector3& p) const {
			return BridgeVector3(vector.Y * p.z() - vector.Z * p.y(), vector.Z * p.x() - vector.X * p.z(), vector.X * p.y() - vector.Y * p.x());
		}
		
		//! Gibt eine String-Darstellung des Vektors wieder
		inline std::wstring toString() { 
			irr::core::stringw str = L"{";
			str += vector.X;
			str += L", ";
			str += vector.Y;
			str += L", ";
			str += vector.Z;
			str += L"}";

			std::wstring stdstring;
			stdstring.append(str.c_str());
			return stdstring;
		}
		inline BridgeVector3& scale(irr::f32 value) { vector*=value; return *this; }
		inline BridgeVector3& normalize() { vector.normalize(); return *this; }
		inline irr::f32 getLength() const { return vector.getLength(); }
		inline irr::f32 getLengthSQ() const { return vector.getLengthSQ(); }
		inline BridgeVector3& setLength(const irr::f32& value) { vector.setLength(value); return *this; }

		//! Binding-Funktion
		static void scriptingBindBridgeVector(HSQUIRRELVM& vm);
	};

}}

#endif
