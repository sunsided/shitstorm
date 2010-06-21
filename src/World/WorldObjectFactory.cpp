/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "WorldObjectFactory.h"
#include "SceneNodes/SceneObject.h"
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
	WorldObjectFactory::WorldObjectFactory() {}

	//! Destruktor
	WorldObjectFactory::~WorldObjectFactory(void) {}

	//! Erzeugt einen Würfel-Knoten
	WorldObject* WorldObjectFactory::CreateCube(PhysicsWorld* world, ISceneManager* mgr, ISceneNode* parent, f32 mass, f32 size, s32 id, vector3df initialPosition) {
		ASSERT(mgr);
		ASSERT(world);

		// Szenenknoten erzeugen
		ISceneNode* sceneNode = mgr->addCubeSceneNode(size, parent, id);
		nodes::SceneObject *sceneObject = new nodes::SceneObject(sceneNode);

		// Kollisionsshape erzeugen
		btCollisionShape* shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
		world->getManager()->registerCollisionShape(shape);

		// Motion State erzeugen
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(conversion::toBulletVector(initialPosition));
		UpdatingPhysicsMotionState* state = new UpdatingPhysicsMotionState(sceneObject, transform);

		// Den Körper erzeugen
		PhysicsObject* body = new RigidBodyPhysicsObject(state, mass, world, shape);
		body->initPhysics();
		world->addObject(body);

		// Weltelement erzeugen
		WorldObject* element = new WorldObject(sceneObject, body);
		return element;
	}

	//! Erzeugt einen beliebigen Knoten
	WorldObject* WorldObjectFactory::Create(physics::PhysicsWorld* world, ISceneNode* sceneNode, btCollisionShape* shape, f32 mass, core::vector3df initialPosition) {
		ASSERT(sceneNode);
		ASSERT(shape);
		ASSERT(world);

		// Szenenobjekt erzeugen
		nodes::SceneObject *sceneObject = new nodes::SceneObject(sceneNode);

		// Durchreichen
		return Create(world, sceneObject, shape, mass, initialPosition);
	}

	//! Erzeugt einen beliebigen Knoten
	WorldObject* WorldObjectFactory::Create(physics::PhysicsWorld* world, nodes::SceneObject *sceneObject, btCollisionShape* shape, f32 mass, core::vector3df initialPosition) {
		ASSERT(sceneObject);
		ASSERT(shape);
		ASSERT(world);

		// Motion State erzeugen
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(conversion::toBulletVector(initialPosition));
		UpdatingPhysicsMotionState* state = new UpdatingPhysicsMotionState(sceneObject, transform);

		// Den Körper erzeugen
		PhysicsObject* body = new RigidBodyPhysicsObject(state, mass, world, shape);
		body->initPhysics();
		world->addObject(body);

		// Weltelement erzeugen
		WorldObject* element = new WorldObject(sceneObject, body);
		return element;
	}

}}