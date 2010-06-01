/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "WorldObject.h"
#include "Physics/UpdatingPhysicsMotionState.h"

using namespace irr;

namespace pv {
namespace world {

	//! Erzeugt eine neue Instanz der WorldElement-Klasse
	WorldObject::WorldObject(nodes::SceneObject* object, physics::PhysicsObject* body) 
		: sceneObject(object), physicsBody(body)
	{
		if (physicsBody) {
			physicsBody->setWorldObject(this);
			if(physicsBody->getMotionState()) copyTranslation(physicsBody->getMotionState()->m_startWorldTrans);
		}
	}

	//! Destruktor
	WorldObject::~WorldObject(void) {
		if (physicsBody) delete physicsBody;
		if (sceneObject) delete sceneObject;
	}

	//! Kopiert die Translation in den Szenenknoten
	void WorldObject::copyTranslation(const btTransform& startTrans) {
		if (sceneObject) {
			// Rotation setzen
			btVector3 rotation;
			physics::PhysicsObject::QuaternionToEulerXYZ(startTrans.getRotation(), rotation);
			sceneObject->getSceneNode()->setRotation(physics::conversion::toIrrlichtVector(rotation));

			// Position setzen
			btVector3 position = startTrans.getOrigin();
			sceneObject->getSceneNode()->setRotation(physics::conversion::toIrrlichtVector(position));
		}
	}

}}