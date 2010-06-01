/** 
 * Project Vector
 * Dynamikwelt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsWorld.h"
#include "PhysicsObject.h"
#include "RigidBodyPhysicsObject.h"
#include <algorithm>

// Bullet
#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {

	//! Destruktor
	PhysicsWorld::~PhysicsWorld(void)
	{
		destruct();
	}
		
	//! Vernichtet die Dynamikwelt
	void PhysicsWorld::destruct() {
		if (!dynamicsWorld) return;

		// Dispatcher löschen
		void* dispatcher = dynamicsWorld->getDispatcher();
		ASSERT(dispatcher);
		delete dispatcher;

		// Broadphase löschen
		void* broadphase = dynamicsWorld->getBroadphase();
		ASSERT(broadphase);
		delete broadphase;

		// Solver löschen
		void* solver = dynamicsWorld->getConstraintSolver();
		ASSERT(solver);
		delete solver;

		// Bodies aus Welt entfernen und löschen
		physicsObjects.iterate(PhysicsWorld::removeObjectFromWorld, this);
		physicsObjects.clear(true);

		// Welt vernichten.
		delete dynamicsWorld;
		dynamicsWorld = NULL;

		// Collision Configuration vernichten
		ASSERT(collisionConfiguration);
		delete collisionConfiguration;
		collisionConfiguration = NULL;
	}

	//! Erzeugt die DefaultCollisionConfiguration
	btCollisionConfiguration* PhysicsWorld::createCollisionConfiguration() const {
		return new btDefaultCollisionConfiguration();
	}

	//! Erzeugt die Collision Dispatcher
	btCollisionDispatcher* PhysicsWorld::createCollisionDispatcher(btCollisionConfiguration* configuration) const {
		ASSERT(configuration);
		return new btCollisionDispatcher(configuration);
	}

	//! Erzeugt den Solver
	btConstraintSolver* PhysicsWorld::createConstraintSolver() const {
		return new btSequentialImpulseConstraintSolver();
	}

	//! Erzeugt die Broadphase
	btBroadphaseInterface* PhysicsWorld::createBroadphase() const {
		return new btDbvtBroadphase();
	}

	//! Erzeugt die eigentliche Welt
	btDynamicsWorld* PhysicsWorld::createDynamicsWorld(
		btCollisionDispatcher* dispatcher,
		btBroadphaseInterface* broadphase,
		btConstraintSolver* solver,
		btCollisionConfiguration* configuration) const {

			return new btDiscreteDynamicsWorld(
				dispatcher, 
				broadphase, 
				solver, 
				configuration);
	}

	//! Ermittelt die Gravitation
	btVector3 PhysicsWorld::getGravity() const {
		return btVector3(0, -9.80665f, 0);
	}

	//! Erzeugt die Welt
	void PhysicsWorld::createWorld() {
		ASSERT(!dynamicsWorld);

		// Collision Configuration erzeugen
		collisionConfiguration = createCollisionConfiguration();
		ASSERT(collisionConfiguration);

		// Collision Dispatcher erzeugen
		btCollisionDispatcher* collisionDispatcher = createCollisionDispatcher(collisionConfiguration);
		ASSERT(collisionDispatcher);

		// Solver erzeugen
		btConstraintSolver* solver = createConstraintSolver();
		ASSERT(solver);

		// Erzeuge Broadphase
		btBroadphaseInterface* broadphase = createBroadphase();
		ASSERT(broadphase);

		// Erzeuge Welt
		dynamicsWorld = createDynamicsWorld(collisionDispatcher, broadphase, solver, collisionConfiguration);
		ASSERT(dynamicsWorld);

		// Gravitation setzen
		dynamicsWorld->setGravity(getGravity());
	}

	//! Fügt der Welt einen Rigid Body hinzu
	/**
	 * @param body	Der hinzuzufügende Körper
	 */
	void PhysicsWorld::addObject(PhysicsObject* body) {
		ASSERT(dynamicsWorld);
		ASSERT(body);

		ASSERT(body->isRigidBody()); // TODO: Soft Bodies
		dynamicsWorld->addRigidBody(dynamic_cast<RigidBodyPhysicsObject*>(body)->getRigidBody());
		physicsObjects.add(body);
	}

	//! Entfernt einen Rigid Body aus der Welt
	/**
	 * @param body	Der zu entfernende Körper
	 */
	void PhysicsWorld::removeObject(PhysicsObject* body) {
		physicsObjects.remove(body);

		ASSERT(body->isRigidBody());
		dynamicsWorld->removeRigidBody(dynamic_cast<RigidBodyPhysicsObject*>(body)->getRigidBody());
	}

	//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
	/**
	* @param deltaTime		Die vergangene Zeit in Sekunden
	* @param maxSubsteps	Die maximale Anzahl Unterschritte
	* @param fixedTimeStep	Der fixe Zeitschritt ... dings. (Konstanter Wert!)
	*/
	void PhysicsWorld::update(float timestep, short unsigned int substeps, float fixedTimeStep) {
		dynamicsWorld->stepSimulation(timestep, substeps, fixedTimeStep);
	}

	//! Entfernt ein Physikobjekt aus einer gegebenen Physikwelt
	void PhysicsWorld::removeObjectFromWorld(PhysicsObject* object, PhysicsWorld* world) {
		ASSERT(object); ASSERT(world);

		// TODO: Unterstützung für beliebige Körper (Soft Bodies, that is)
		ASSERT(object->isRigidBody());
		world->dynamicsWorld->removeRigidBody(dynamic_cast<RigidBodyPhysicsObject*>(object)->getRigidBody());
	}
}}
