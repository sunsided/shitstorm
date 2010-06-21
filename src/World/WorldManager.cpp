/** 
 * Project Vector
 * Weltmanagement
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "WorldManager.h"
#include "Physics/PhysicsObject.h"
#include "SceneNodes/SceneObject.h"

namespace pv {
namespace world {

	//! Destruktor
	WorldManager::~WorldManager(void)
	{
		worldObjectManager.clear(true);
	}


	//! Erzeugt ein Weltobjekt
	WorldObject* WorldManager::createWorldObject(nodes::SceneObject* sceneObject, physics::PhysicsObject* physicsObject) {
		
		WorldObject* worldObject = new WorldObject(sceneObject, physicsObject);
		return addWorldObject(worldObject);
	}

	//! Hängt ein Weltobjekt ein
	WorldObject* WorldManager::addWorldObject(WorldObject* worldObject) {
		irr::s32 id = worldObjectManager.add(worldObject);
		worldObject->setWorldObjectId(id);
		return worldObject;
	}

	//! Entfernt ein Weltobjekt
	void WorldManager::removeWorldObject(WorldObject* worldObject) {
		worldObjectManager.remove(worldObject);
	}

	//! Entfernt ein Weltobjekt
	void WorldManager::removeWorldObject(irr::u32 worldObjectId) {
		worldObjectManager.remove(worldObjectId);
	}

}}
