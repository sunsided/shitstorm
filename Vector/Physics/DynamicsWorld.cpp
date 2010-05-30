/** 
 * Project Vector
 * Dynamikwelt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "DynamicsWorld.h"

// Bullet
#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {

	//! Destruktor
	DynamicsWorld::~DynamicsWorld(void)
	{
		destruct();
	}
		
	//! Vernichtet die Dynamikwelt
	void DynamicsWorld::destruct() {
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

		// Bodies entfernen
		while (!rigidBodies.empty()) {
			btRigidBody* body = rigidBodies.back();
			rigidBodies.pop_back();
			dynamicsWorld->removeRigidBody(body);
		}

		// Welt vernichten.
		delete dynamicsWorld;
		dynamicsWorld = NULL;

		// Collision Configuration vernichten
		ASSERT(collisionConfiguration);
		delete collisionConfiguration;
		collisionConfiguration = NULL;
	}

	//! Erzeugt die DefaultCollisionConfiguration
	btDefaultCollisionConfiguration* DynamicsWorld::createCollisionConfiguration() const {
		return new btDefaultCollisionConfiguration();
	}

	//! Erzeugt die Collision Dispatcher
	btCollisionDispatcher* DynamicsWorld::createCollisionDispatcher(btDefaultCollisionConfiguration* configuration) const {
		ASSERT(configuration);
		return new btCollisionDispatcher(configuration);
	}

	//! Erzeugt den Solver
	btConstraintSolver* DynamicsWorld::createConstraintSolver() const {
		return new btSequentialImpulseConstraintSolver();
	}

	//! Erzeugt die Broadphase
	btBroadphaseInterface* DynamicsWorld::createBroadphase() const {
		return new btDbvtBroadphase();
	}

	//! Erzeugt die eigentliche Welt
	btDiscreteDynamicsWorld* DynamicsWorld::createDynamicsWorld(
		btCollisionDispatcher* dispatcher,
		btBroadphaseInterface* broadphase,
		btConstraintSolver* solver,
		btDefaultCollisionConfiguration* configuration) const {

			return new btDiscreteDynamicsWorld(
				dispatcher, 
				broadphase, 
				solver, 
				configuration);
	}

	//! Ermittelt die Gravitation
	btVector3 DynamicsWorld::getGravity() const {
		return btVector3(0, -9.80665f, 0);
	}

	//! Erzeugt die Welt
	void DynamicsWorld::createWorld() {

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
	void DynamicsWorld::addRigidBody(btRigidBody* body) {
		ASSERT(dynamicsWorld);
		ASSERT(body);

		dynamicsWorld->addRigidBody(body);
		rigidBodies.push_back(body);
	}
}}
