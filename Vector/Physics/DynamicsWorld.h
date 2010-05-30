/** 
 * Project Vector
 * Dynamikwelt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _DYNAMICSWORLD_H
#define _DYNAMICSWORLD_H

#include "global.h"
#include <vector>

// Vorwärtsdeklaration der Klassen
class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btRigidBody;
class btCollisionDispatcher;
class btConstraintSolver;
class btBroadphaseInterface;
class btVector3;

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine verwaltet
	class DynamicsWorld
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		DynamicsWorld(void) : dynamicsWorld(NULL), collisionConfiguration(NULL) {}

		//! Destruktor
		virtual ~DynamicsWorld(void);

		//! Erzeugt die Welt
		void createWorld();

		//! Ermittelt, ob die Dynamikwelt initialisiert wurde
		inline bool isInitialized() const { return dynamicsWorld != NULL; }

		//! Fügt der Welt einen Rigid Body hinzu
		/**
		 * @param body	Der hinzuzufügende Körper
		 */
		void addRigidBody(btRigidBody* body);

		//! Entfernt einen Rigid Body aus der Welt.
		/** Die Funktion ist nur schnell, wenn die Objekte in umgekehrter Reihenfolge entfernt werden.
		 *	Ist dies nicht der Fall, wird eine lineare Suche gestartet.
		 * @param body	Das zu entfernende Element
		 */
		void removeRigidBody(btRigidBody* body);

	protected:

		//! Erzeugt die DefaultCollisionConfiguration
		virtual btDefaultCollisionConfiguration* createCollisionConfiguration() const;

		//! Erzeugt die Collision Dispatcher
		virtual btCollisionDispatcher* createCollisionDispatcher(btDefaultCollisionConfiguration* configuration) const;

		//! Erzeugt den Solver
		virtual btConstraintSolver* createConstraintSolver() const;

		//! Erzeugt die Broadphase
		virtual btBroadphaseInterface* createBroadphase() const;

		//! Erzeugt die eigentliche Welt
		virtual btDiscreteDynamicsWorld* createDynamicsWorld(
			btCollisionDispatcher* dispatcher,
			btBroadphaseInterface* broadphase,
			btConstraintSolver* solver,
			btDefaultCollisionConfiguration* configuration) const;

		//! Ermittelt die Gravitation
		virtual btVector3 getGravity() const;

	private:
		
		//! Vernichtet die Dynamikwelt
		void destruct();

	private:

		//! Die tatsächlich verwendete Dynamikwelt
		btDiscreteDynamicsWorld* dynamicsWorld;

		//! Die Collision Configuration
		btDefaultCollisionConfiguration* collisionConfiguration;

		//! Sammlung aller Rigid Bodies
		std::vector<btRigidBody*> rigidBodies;

	};

}}

#endif
