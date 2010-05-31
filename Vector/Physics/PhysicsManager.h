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

#include "GameLogic/Manager.h"
#include "PhysicsWorld.h"

//! Vorwärtsdeklaration der Klasse
class btCollisionShape;

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine verwaltet
	class PhysicsManager
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsManager(void);

		//! Destruktor
		virtual ~PhysicsManager(void);

		//! Initialisiert die Physikengine
		void initialize();

		//! Holt den Collision Shape Manager
		inline const Manager<btCollisionShape>& getCollisionShapeManager() const { return collisionShapeManager; }

		//! Fügt dem System eine Dynamikwelt hinzu.
		/** Alle hier registrierten Welten werden automatisch vom System vernichtet.
		 *	Ein zusätzlicher Aufruf von delete ist nicht nötig!
		 * @param world		Die hinzuzufügende Welt
		 */
		irr::u32 addPhysicsWorld(PhysicsWorld *world);

		//! Erzeugt eine neue Physikwelt und registriert sie
		PhysicsWorld * createPhysicsWorld();

		//! Erzeugt eine neue Physikwelt und registriert sie
		inline PhysicsWorld* getPhysicsWorld(unsigned int worldId) { return dynamicsWorldManager.getElement(worldId); }

		//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
		/** Aktualisiert alle registrierten Dynamikwelten.
		* @param deltaTime		Die vergangene Zeit in Sekunden
		* @param maxSubsteps	Die maximale Anzahl Unterschritte
		* @param fixedTimeStep	Der fixe Zeitschritt; Bullet-Standard ist 1/60
		*/
		void update(float deltaTime, short unsigned int maxSubsteps = 10, float fixedTimeStep = 1.0f/60.0f);

		//! Ermittelt ein Collision Shape anhand seiner Id
		inline btCollisionShape* getCollisionShape(unsigned int shapeId) { return collisionShapeManager.getElement(shapeId); }

		//! Registriert ein Collision shape
		irr::u32 registerCollisionShape(btCollisionShape* shape);

	protected:

		//! Löscht alle DynamicsWorld-Instanzen
		void cleanupDynamicsWorlds();

	private:
		
		//! Gibt an, ob die Engine initialisiert wurde
		bool initialized;
		
		//! Die Simulationswelten
		Manager<PhysicsWorld> dynamicsWorldManager;

		//! Manager für Collision Shapes
		Manager<btCollisionShape> collisionShapeManager;
	};

}}

#endif
