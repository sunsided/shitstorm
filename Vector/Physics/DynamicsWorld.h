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
		void addRigidBody(btRigidBody* body);

	protected:

		//! Erzeugt die DefaultCollisionConfiguration
		virtual btDefaultCollisionConfiguration* createCollisionConfiguration();

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
