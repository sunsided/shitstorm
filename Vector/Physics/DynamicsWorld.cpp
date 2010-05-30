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
	btDefaultCollisionConfiguration* DynamicsWorld::createCollisionConfiguration() {
		return new btDefaultCollisionConfiguration();
	}

	//! Erzeugt die Welt
	void DynamicsWorld::createWorld() {

		// Collision Configuration erzeugen
		collisionConfiguration = createCollisionConfiguration();
	}

	//! Fügt der Welt einen Rigid Body hinzu
	void DynamicsWorld::addRigidBody(btRigidBody* body) {
		ASSERT(dynamicsWorld);
		ASSERT(body);

		dynamicsWorld->addRigidBody(body);
		rigidBodies.push_back(body);
	}
}}
