/** 
 * Project Vector
 * Physikmanagement
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsManagement.h"

// Bullet
#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {

	//! Erzeugt eine neue Instanz des Objektes
	PhysicsManagement::PhysicsManagement(void) : 
		initialized(false),
		collisionShapeManager(NULL)
	{
	}

	//! Destruktor
	PhysicsManagement::~PhysicsManagement(void)
	{
		cleanupDynamicsWorlds();
		if (collisionShapeManager) delete collisionShapeManager;
	}

	//! Initialisiert die Physikengine
	void PhysicsManagement::initialize() {

		// Aufräumen
		if (collisionShapeManager) delete collisionShapeManager;
		cleanupDynamicsWorlds();

		// Neue Instanzen erstellen
		collisionShapeManager = new CollisionShapeManagement();
	}

	//! Löscht alle DynamicsWorld-Instanzen
	void PhysicsManagement::cleanupDynamicsWorlds() {
		while(!dynamicsWorlds.empty()) {

			// Letzte Welt ermitteln und aus Vektor entfernen
			PhysicsWorld* world = dynamicsWorlds.back();
			dynamicsWorlds.pop_back();

			// Welt freigeben
			delete world;
		}
	}

	//! Fügt dem System eine Dynamikwelt hinzu
	void PhysicsManagement::addDynamicsWorld(PhysicsWorld *world) {
		ASSERT(world);
		dynamicsWorlds.push_back(world);
	}

	//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
	/** Aktualisiert alle registrierten Dynamikwelten.
	* @param deltaTime		Die vergangene Zeit in Sekunden
	* @param maxSubsteps	Die maximale Anzahl Unterschritte
	* @param fixedTimeStep	Der fixe Zeitschritt; Bullet-Standard ist 1/60
	*/
	void PhysicsManagement::update(float deltaTime, short unsigned int maxSubsteps, float fixedTimeStep) {
		
		// http://msdn.microsoft.com/en-us/library/dd647617.aspx
		std::vector<PhysicsWorld*>::const_iterator iterator = dynamicsWorlds.cbegin();
		for (; iterator != dynamicsWorlds.cend(); iterator++)
		{
			(*iterator)->update(deltaTime, maxSubsteps, fixedTimeStep);
		}
	}

}}
