/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "WorldElementFactory.h"
#include "Physics/UpdatingPhysicsMotionState.h"
#include "Physics/PhysicsManager.h"
#include "Physics/RigidBodyPhysicsObject.h"

using namespace irr;
using namespace scene;
using namespace core;

namespace pv {

using namespace physics;

namespace world
{
	//! Erzeugt eine neue Instanz der WorldElementFactory-Klasse
	WorldElementFactory::WorldElementFactory() {}

	//! Destruktor
	WorldElementFactory::~WorldElementFactory(void) {}

	//! Erzeugt einen Würfel-Knoten
	WorldElement* WorldElementFactory::CreateCubeElement(PhysicsWorld* world, ISceneManager* mgr, ISceneNode* parent, f32 mass, f32 size, s32 id, vector3df initialPosition) {
		ASSERT(mgr);
		ASSERT(world);

		// Szenenknoten erzeugen
		ISceneNode* sceneNode = mgr->addCubeSceneNode(size, parent, id);

		// Kollisionsshape erzeugen
		btCollisionShape* shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
		world->getManager()->registerCollisionShape(shape);

		// Motion State erzeugen
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(conversion::toBulletVector(initialPosition));
		UpdatingPhysicsMotionState* state = new UpdatingPhysicsMotionState(sceneNode, transform);

		// Den Körper erzeugen
		PhysicsObject* body = new RigidBodyPhysicsObject(state, mass, world, shape);
		body->initPhysics();
		world->addBody(body);

		// Weltelement erzeugen
		WorldElement* element = new WorldElement(sceneNode, body);
		return element;
	}

	//! Erzeugt einen beliebigen Knoten
	WorldElement* WorldElementFactory::CreateElement(physics::PhysicsWorld* world, ISceneNode* sceneNode, btCollisionShape* shape, f32 mass, core::vector3df initialPosition) {
		ASSERT(sceneNode);
		ASSERT(shape);
		ASSERT(world);

		// Motion State erzeugen
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(conversion::toBulletVector(initialPosition));
		UpdatingPhysicsMotionState* state = new UpdatingPhysicsMotionState(sceneNode, transform);

		// Den Körper erzeugen
		PhysicsObject* body = new RigidBodyPhysicsObject(state, mass, world, shape);
		body->initPhysics();
		world->addBody(body);

		// Weltelement erzeugen
		WorldElement* element = new WorldElement(sceneNode, body);
		return element;
	}

}}