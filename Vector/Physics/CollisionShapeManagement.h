/** 
 * Project Vector
 * Verwaltung der Collision Shapes
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _DYNAMICSWORLD_H
#define _DYNAMICSWORLD_H

#include "global.h"
#include <vector>

// Vorwärtsdeklaration der Klassen
class btCollisionShape;

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine verwaltet
	class CollisionShapeManagement
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		CollisionShapeManagement(void) {}

		//! Destruktor
		virtual ~CollisionShapeManagement(void);

		//! Registriert ein Collision Shape
		unsigned int registerCollisionShape(const btCollisionShape* shape);

		//! Ermittelt ein Collision Shape anhand seiner ID
		const btCollisionShape* getCollisionShape(unsigned int collisionShapeId);

		//! Liefert die Anzahl der registrierten Elemente
		inline size_t count() const { return collisionShapes.capacity(); }
		
	private:
		
		//! Vernichtet die Dynamikwelt
		void destruct();

	private:

		//! Sammlung aller Shapes
		std::vector<const btCollisionShape*> collisionShapes;

	};

}}

#endif
