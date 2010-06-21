/** 
 * Project Vector
 * Physikmanagement
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsManager.h"

// Bullet
#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {

	//! Erzeugt eine neue Instanz des Objektes
	PhysicsManager::PhysicsManager(void) : 
		initialized(false),
		collisionShapeManager(true),
		dynamicsWorldManager(true)
	{
	}

	//! Destruktor
	PhysicsManager::~PhysicsManager(void)
	{
		cleanupDynamicsWorlds();
		collisionShapeManager.clear();
	}

	//! Initialisiert die Physikengine
	void PhysicsManager::initialize() {

		// Aufräumen
		collisionShapeManager.clear();
		cleanupDynamicsWorlds();
	}

	//! Löscht alle DynamicsWorld-Instanzen
	void PhysicsManager::cleanupDynamicsWorlds() {
		dynamicsWorldManager.clear();
	}

	//! Fügt dem System eine Dynamikwelt hinzu
	irr::u32 PhysicsManager::addPhysicsWorld(PhysicsWorld *world) {
		ASSERT(world);
		return dynamicsWorldManager.add(world);
	}

	//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
	/** Aktualisiert alle registrierten Dynamikwelten.
	* @param deltaTime		Die vergangene Zeit in Sekunden
	* @param maxSubsteps	Die maximale Anzahl Unterschritte
	* @param fixedTimeStep	Der fixe Zeitschritt; Bullet-Standard ist 1/60
	*/
	void PhysicsManager::update(float deltaTime, short unsigned int maxSubsteps, float fixedTimeStep) {
		
		PhysicsWorld::UpdateState updateState(deltaTime, maxSubsteps, fixedTimeStep);
		dynamicsWorldManager.iterate(PhysicsWorld::updateWorld, &updateState);

	}

	//! Erzeugt eine neue Physikwelt und registriert sie
	PhysicsWorld* PhysicsManager::createPhysicsWorld() {
		physics::PhysicsWorld *world = new physics::PhysicsWorld(this);
		ASSERT(world);

		world->createWorld();
		addPhysicsWorld(world);
		return world;
	}

	//! Registriert ein Collision shape
	irr::u32 PhysicsManager::registerCollisionShape(btCollisionShape* shape) {
		ASSERT(shape);
		if (collisionShapeManager.contains(shape)) return collisionShapeManager.getId(shape);
		return collisionShapeManager.add(shape);
	}

}}
