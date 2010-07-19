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
		// DebugRenderer entsorgen
		removeDebugRenderer();

		// Keine Dynamikwelt? Und tschüss!
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
		
		// Ghost Objects aus Welt entfernen und löschen
		ghostObjects.iterate(PhysicsWorld::removeObjectFromWorld, this);
		ghostObjects.clear(true);

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

		// Renderer setzen
		if (debugRenderer) dynamicsWorld->setDebugDrawer(debugRenderer);

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

	//! Fügt der Welt einen Rigid Body hinzu
	/**
	 * @param body	Der hinzuzufügende Körper
	 */
	void PhysicsWorld::addObject(CollisionDetectionPhysicsObject* body) {
		ASSERT(dynamicsWorld);
		ASSERT(body);

		dynamicsWorld->addCollisionObject(body->getCollisionObject());
		ghostObjects.add(body);
	}

	//! Entfernt einen Rigid Body aus der Welt
	/**
	 * @param body	Der zu entfernende Körper
	 */
	void PhysicsWorld::removeObject(CollisionDetectionPhysicsObject* body) {
		ghostObjects.remove(body);
		dynamicsWorld->removeCollisionObject(body->getCollisionObject());
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

	//! Entfernt ein Geistobjekt aus einer gegebenen Physikwelt
	void PhysicsWorld::removeObjectFromWorld(CollisionDetectionPhysicsObject* object, PhysicsWorld* world) {
		ASSERT(object); ASSERT(world);
		world->dynamicsWorld->removeCollisionObject(object->getCollisionObject());
	}

	//! Setzt den Debug-Renderer
	void PhysicsWorld::setDebugRenderer(irr::video::IVideoDriver* driver) {
		removeDebugRenderer();

		debugRenderer = new PhysicsDebugRenderer(driver);
		if (dynamicsWorld) dynamicsWorld->setDebugDrawer(debugRenderer);
	}

	//! Entfernt den Debug-Renderer
	void PhysicsWorld::removeDebugRenderer() { 
		if (!debugRenderer) return;
		if (dynamicsWorld) dynamicsWorld->setDebugDrawer(NULL);
		
		delete debugRenderer; 
		debugRenderer = NULL;
	}
}}
