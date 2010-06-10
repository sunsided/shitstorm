/** 
 * Project Vector
 * Weltmanagement
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _WORLDMANAGEMENT_H
#define _WORLDMANAGEMENT_H

#include "global.h"
#include "Utility/Manager.h"
#include "WorldObject.h"
#include "Scripting/Bindings/WorldBindings.h"

namespace pv {
	namespace physics { class PhysicsObject; }
	namespace nodes { class SceneObject; }

namespace world {

	//! Klasse, die die Welt verwaltet
	class WorldManager
	{
		friend class pv::scripting::WorldBindings;

	public:
		//! Erzeugt eine neue Instanz des Objektes
		WorldManager(void) 
			: worldObjectManager(true)
		{}

		//! Destruktor
		virtual ~WorldManager(void);

		//! Erzeugt ein Weltobjekt
		WorldObject* createWorldObject(nodes::SceneObject* sceneObject = NULL, physics::PhysicsObject* physicsObject = NULL);

		//! Hängt ein Weltobjekt ein
		WorldObject* addWorldObject(WorldObject* worldObject);

		//! Entfernt ein Weltobjekt
		void removeWorldObject(WorldObject* worldObject);

		//! Entfernt ein Weltobjekt
		void removeWorldObject(irr::u32 worldObjectId);

		//! Liefert die Anzahl der registrierten Elemente
		inline irr::u32 worldObjectCount() { return worldObjectManager.count(); }

		//! Entfernt und löscht alle Objekte
		inline void clearAllObjects() { worldObjectManager.clear(); }

	private:

		//! Manager für Collision Shapes
		utility::Manager<WorldObject> worldObjectManager;
	};

}}

#endif
