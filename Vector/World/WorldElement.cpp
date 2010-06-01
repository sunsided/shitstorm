/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "WorldElement.h"
#include "Physics/UpdatingPhysicsMotionState.h"

using namespace irr;

namespace pv {
namespace world {

	//! Erzeugt eine neue Instanz der WorldElement-Klasse
	WorldElement::WorldElement(nodes::SceneObject* object, physics::PhysicsObject* body) 
		: sceneObject(object), physicsBody(body)
	{
		if (physicsBody) {
			physicsBody->setWorldElement(this);
			if(physicsBody->getMotionState()) copyTranslation(physicsBody->getMotionState()->m_startWorldTrans);
		}
	}

	//! Kopiert die Translation in den Szenenknoten
	void WorldElement::copyTranslation(const btTransform& startTrans) {
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

	//! Destruktor
	WorldElement::~WorldElement(void) {
		if (physicsBody) delete physicsBody;
		if (sceneObject) delete sceneObject;
	}

}}