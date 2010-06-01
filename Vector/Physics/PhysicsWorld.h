/** 
 * Project Vector
 * Dynamikwelt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSWORLD_H
#define _PHYSICSWORLD_H

#include "global.h"
#include "GameLogic/Manager.h"
#include "PhysicsObject.h"

// Vorwärtsdeklaration der Klassen
class btDynamicsWorld;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btConstraintSolver;
class btBroadphaseInterface;

namespace pv {
namespace physics {

	// Vorwärtsdeklaration der Klassen
	class PhysicsManager;

	//! Klasse, die die Physikengine darstellt
	class PhysicsWorld
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		PhysicsWorld(PhysicsManager* manager) : dynamicsWorld(NULL), collisionConfiguration(NULL), physicsManager(manager)
		{
			ASSERT(manager);
		}

		//! Destruktor
		virtual ~PhysicsWorld(void);

		//! Erzeugt die Welt
		void createWorld();

		//! Ermittelt, ob die Dynamikwelt initialisiert wurde
		inline bool isInitialized() const { return dynamicsWorld != NULL; }

		//! Fügt der Welt ein Physikobjekt hinzu
		/**
		 * @param body	Der hinzuzufügende Körper
		 */
		void addObject(PhysicsObject* body);

		//! Entfernt Physikobjekt aus der Welt.
		/** 
		 * @param body	Das zu entfernende Element
		 */
		void removeObject(PhysicsObject* body);

		//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
		/**
		* @param deltaTime		Die vergangene Zeit in Sekunden
		* @param maxSubsteps	Die maximale Anzahl Unterschritte
		* @param fixedTimeStep	Der fixe Zeitschritt; Bullet-Standard ist 1/60
		*/
		void update(float deltaTime, short unsigned int maxSubsteps = 10, float fixedTimeStep = 1.0f/60.0f);

	protected:

		//! Erzeugt die DefaultCollisionConfiguration
		virtual btCollisionConfiguration* createCollisionConfiguration() const;

		//! Erzeugt die Collision Dispatcher
		virtual btCollisionDispatcher* createCollisionDispatcher(btCollisionConfiguration* configuration) const;

		//! Erzeugt den Solver
		virtual btConstraintSolver* createConstraintSolver() const;

		//! Erzeugt die Broadphase
		virtual btBroadphaseInterface* createBroadphase() const;

		//! Erzeugt die eigentliche Welt
		virtual btDynamicsWorld* createDynamicsWorld(
			btCollisionDispatcher* dispatcher,
			btBroadphaseInterface* broadphase,
			btConstraintSolver* solver,
			btCollisionConfiguration* configuration) const;

	public:

		//! Ermittelt die Gravitation
		virtual btVector3 getGravity() const;

		//! Bezieht die Dynamikwelt
		virtual btDynamicsWorld* getDynamicsWorld() const { return dynamicsWorld; }

		//! Bezieht den Manager
		PhysicsManager* getManager() const { return physicsManager; }

	private:
		
		//! Vernichtet die Dynamikwelt
		void destruct();

	private:

		//! Die tatsächlich verwendete Dynamikwelt
		btDynamicsWorld* dynamicsWorld;

		//! Die Collision Configuration
		btCollisionConfiguration* collisionConfiguration;

		//! Sammlung aller Rigid Bodies
		Manager<PhysicsObject> physicsObjects;

		//! Liefert den Manager
		PhysicsManager* physicsManager;

	public:

		//! Struktur, die zum Updaten einer Welt verwendet werden kann
		typedef struct SUpdateState {
			float deltaTime;
			short unsigned int maxSubsteps;
			float fixedTimeStep;

			inline SUpdateState(float deltaTime, short unsigned int maxSubsteps, float fixedTimeStep) 
				: deltaTime(deltaTime), maxSubsteps(maxSubsteps), fixedTimeStep(fixedTimeStep)
			{}
		} UpdateState;

		//! Aktualisiert eine Welt
		inline static void updateWorld(PhysicsWorld* world, PhysicsWorld::UpdateState* state) {
			ASSERT(world); ASSERT(state);
			world->update(state->deltaTime, state->maxSubsteps, state->fixedTimeStep);
		}

		//! Entfernt ein Physikobjekt aus einer gegebenen Physikwelt
		static void removeObjectFromWorld(PhysicsObject* object, PhysicsWorld* world);

	};

}}

#endif
