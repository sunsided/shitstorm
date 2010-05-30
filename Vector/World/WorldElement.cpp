/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "WorldElement.h"

namespace pv {
namespace world
{
	
	//! Erzeugt eine neue Instanz der WorldElement-Klasse
	WorldElement::WorldElement(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id,
			const btTransform& startTrans, 
			const btTransform& centerOfMassOffset,
			f32 mass,
			physics::PhysicsWorld* physicsWorld,
			btCollisionShape* collisionShape
			)
		: 
		irr::scene::ISceneNode(parent, mgr, id),
		physics::PhysicsBody(startTrans, centerOfMassOffset, mass, physicsWorld, collisionShape)
	{		
		// Rotation setzen
		btVector3 rotation;
		physics::PhysicsBody::QuaternionToEulerXYZ(startTrans.getRotation(), rotation);
		irr::scene::ISceneNode::setRotation(physics::conversion::toIrrlichtVector(rotation));

		// Position setzen
		btVector3 position = startTrans.getOrigin();
		irr::scene::ISceneNode::setRotation(physics::conversion::toIrrlichtVector(position));
	}

	//! Erzeugt eine neue Instanz der WorldElement-Klasse
	WorldElement::WorldElement(irr::scene::ISceneNode& node, physics::PhysicsBody& body) 
		: irr::scene::ISceneNode(node), physics::PhysicsBody(body)
	{

	}

	//! Aktualisiert die Welttransformation.
	/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
	* @param worldTrans	Die zu setzende Transformation
	*/
	void WorldElement::setWorldTransform(const btTransform& worldTrans) {
		PhysicsBody::setWorldTransform(worldTrans);

		// Rotation übernehmen
		irr::core::vector3df rotation = physics::PhysicsBody::getRotation();
		irr::scene::ISceneNode::setRotation(rotation);

		// Position übernehmen
		irr::core::vector3df position = physics::PhysicsBody::getPosition();
		irr::scene::ISceneNode::setPosition(position);
	}

}}