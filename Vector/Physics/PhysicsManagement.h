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

namespace pv {
namespace physics {

	// Vorwärtsdeklarationen der Klassen
	class btBroadphaseInterface;
	class btDefaultCollisionConfiguration;
	class btCollisionDispatcher;
	class btSequentialImpulseConstraintSolver;
	class btDiscreteDynamicsWorld;

	//! Klasse, die die Physikengine verwaltet
	class PhysicsManagement
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsManagement(void) : 
			initialized(false), 
			broadphase(NULL), 
			collisionConfiguration(NULL),
			collisionDispatcher(NULL),
			solver(NULL)
		{}

		//! Destruktor
		virtual ~PhysicsManagement(void);

		//! Initialisiert die Physikengine
		void initialize();

	protected:

		//! Löscht alle DynamicsWorld-Instanzen
		void cleanupDynamicsWorlds();

	private:
		
		//! Gibt an, ob die Engine initialisiert wurde
		bool initialized;

		//! Die verwendete Broadphase
		btBroadphaseInterface* broadphase;

		//! Kollisionskonfiguration
		btDefaultCollisionConfiguration* collisionConfiguration;

		//! Kollisionsdispatcher
		btCollisionDispatcher* collisionDispatcher;

		//! Der Solver
		btSequentialImpulseConstraintSolver* solver;

		//! Die Simulationswelt
		std::vector<btDiscreteDynamicsWorld*> dynamicsWorlds;
	};

}}

#endif
