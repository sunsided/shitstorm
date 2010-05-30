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

	//! Destruktor
	PhysicsManagement::~PhysicsManagement(void)
	{
	}

	//! Initialisiert die Physikengine
	void PhysicsManagement::initialize() {
		cleanupDynamicsWorlds();
	}

	//! Löscht alle DynamicsWorld-Instanzen
	void PhysicsManagement::cleanupDynamicsWorlds() {
		/*
		while(!dynamicsWorlds.empty()) {

			// Letzte Welt ermitteln und aus Vektor entfernen
			btDiscreteDynamicsWorld* world = dynamicsWorlds.back();
			dynamicsWorlds.pop_back();

			// Welt freigeben
			delete world;
		}
		*/
	}

}}
