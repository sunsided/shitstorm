/** 
 * Project Vector
 * Physikmanagement
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSMANAGEMENT_H
#define _PHYSICSMANAGEMENT_H

#include "global.h"
#include <vector>

#include "DynamicsWorld.h"
#include "CollisionShapeManagement.h"

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine verwaltet
	class PhysicsManagement
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsManagement(void);

		//! Destruktor
		virtual ~PhysicsManagement(void);

		//! Initialisiert die Physikengine
		void initialize();

		//! Holt den Collision Shape Manager
		inline CollisionShapeManagement* getCollisionShapeManagement() const { return collisionShapeManager; }

		//! Fügt dem System eine Dynamikwelt hinzu
		void addDynamicsWorld(DynamicsWorld *world);

		//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
		/** Aktualisiert alle registrierten Dynamikwelten.
		* @param deltaTime		Die vergangene Zeit in Sekunden
		* @param maxSubsteps	Die maximale Anzahl Unterschritte
		* @param fixedTimeStep	Der fixe Zeitschritt; Bullet-Standard ist 1/60
		*/
		void update(float deltaTime, short unsigned int maxSubsteps = 10, float fixedTimeStep = 1.0f/60.0f);

	protected:

		//! Löscht alle DynamicsWorld-Instanzen
		void cleanupDynamicsWorlds();

	private:
		
		//! Gibt an, ob die Engine initialisiert wurde
		bool initialized;
		
		//! Die Simulationswelt
		std::vector<DynamicsWorld*> dynamicsWorlds;

		//! Die CollisionShapeManagement-Instanz
		CollisionShapeManagement* collisionShapeManager;
	};

}}

#endif
