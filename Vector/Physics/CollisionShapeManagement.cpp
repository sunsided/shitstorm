/** 
 * Project Vector
 * Verwaltung der Collision Shapes
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "CollisionShapeManagement.h"
#include <algorithm>

// Bullet
#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {

	//! Destruktor
	CollisionShapeManagement::~CollisionShapeManagement(void)
	{
		destruct();
	}
		
	//! Vernicht die Kollisionsshapes
	void CollisionShapeManagement::destruct() {

		// Bodies entfernen
		while (!collisionShapes.empty()) {
			const btCollisionShape* shape = collisionShapes.back();
			collisionShapes.pop_back();
			
			// Shape löschen
			if (shape) delete shape;
		}
	}

	//! Registriert ein Collision Shape
	unsigned int CollisionShapeManagement::registerCollisionShape(const btCollisionShape* shape) {
		collisionShapes.push_back(shape);
		return collisionShapes.capacity() - 1;
	}

	//! Ermittelt ein Collision Shape anhand seiner ID
	const btCollisionShape* CollisionShapeManagement::getCollisionShape(unsigned int collisionShapeId) {
		return collisionShapes.at(collisionShapeId);
	}
}}
