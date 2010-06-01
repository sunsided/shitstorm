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

		// Bodies entfernen
		while (!rigidBodies.empty()) {
			PhysicsObject* body = rigidBodies.back();
			rigidBodies.pop_back();

			// TODO: Unterstützung für beliebige Körper (Soft Bodies, that is)
			ASSERT(body->isRigidBody());
			dynamicsWorld->removeRigidBody(dynamic_cast<RigidBodyPhysicsObject*>(body)->getRigidBody());
			
			// Motion State des Bodies und den Body selbst löschen
			// Das Collision Shape wird vom CollisionShapeManagement entsorgt
			delete body->getMotionState();
			delete body;
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
	void PhysicsWorld::addBody(PhysicsObject* body) {
		ASSERT(dynamicsWorld);
		ASSERT(body);

		ASSERT(body->isRigidBody()); // TODO: Soft Bodies
		dynamicsWorld->addRigidBody(dynamic_cast<RigidBodyPhysicsObject*>(body)->getRigidBody());
		rigidBodies.push_back(body);
	}

	//! Entfernt einen Rigid Body aus der Welt
	/**
	 * @param body	Der zu entfernende Körper
	 */
	void PhysicsWorld::removeBody(PhysicsObject* body) {

		// TODO: Entfernen von Elementen optimieren
		if (body == rigidBodies.back()) {
			rigidBodies.pop_back();
		}
		else {
			// http://www.codeguru.com/forum/showthread.php?t=231045
			rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), body), rigidBodies.end());
		}

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
}}
