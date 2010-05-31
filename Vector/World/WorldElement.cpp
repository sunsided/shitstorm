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

using namespace physics;

namespace world
{
	
	//! Erzeugt eine neue Instanz der WorldElement-Klasse
	WorldElement::WorldElement(scene::ISceneNode* node,
			const btTransform& startTrans, 
			const btTransform& centerOfMassOffset,
			f32 mass,
			physics::PhysicsWorld* physicsWorld,
			btCollisionShape* collisionShape
			) :
			sceneNode(node)
	{		
		
		// Motion State und Physikkörper erzeugen
		UpdatingPhysicsMotionState* state = new UpdatingPhysicsMotionState(node, startTrans, centerOfMassOffset);
		physicsBody = new PhysicsBody(state, mass, physicsWorld, collisionShape);
		ASSERT(physicsBody);
		physicsBody->setWorldElement(this);

		// Translation setzen
		copyTranslation(startTrans);
	}

	//! Erzeugt eine neue Instanz der WorldElement-Klasse
	WorldElement::WorldElement(scene::ISceneNode* node, physics::PhysicsBody* body) 
		: sceneNode(node), physicsBody(body)
	{
		if (physicsBody) {
			physicsBody->setWorldElement(this);
			if(physicsBody->getMotionState()) copyTranslation(physicsBody->getMotionState()->m_startWorldTrans);
		}
	}

	//! Kopiert die Translation in den Szenenknoten
	void WorldElement::copyTranslation(const btTransform& startTrans) {
		if (sceneNode) {
			// Rotation setzen
			btVector3 rotation;
			physics::PhysicsBody::QuaternionToEulerXYZ(startTrans.getRotation(), rotation);
			sceneNode->setRotation(physics::conversion::toIrrlichtVector(rotation));

			// Position setzen
			btVector3 position = startTrans.getOrigin();
			sceneNode->setRotation(physics::conversion::toIrrlichtVector(position));
		}
	}

	//! Destruktor
	WorldElement::~WorldElement(void) {
		if (physicsBody) delete physicsBody;
	}

}}