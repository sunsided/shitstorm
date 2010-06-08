/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _WORLDOBJECT_H
#define _WORLDOBJECT_H

#include "global.h"
#include "Physics/PhysicsObject.h"
#include "SceneNodes/SceneObject.h"
#include "Scripting/Bindings/BridgeVector3.h"

namespace pv {
namespace world {

	// Vorwärtsdeklaration der Klassen
	class WorldManager;

	//! Ein Element in der Spielwelt
	class WorldObject
	{
		friend class WorldManager;

	public:

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldObject(nodes::SceneObject* object = NULL, physics::PhysicsObject* body = NULL);
		
		//! Destruktor
		virtual ~WorldObject(void);
	
	private:

		//! Kopiert die Translation in den Szenenknoten
		void copyTranslation(const btTransform& startTrans);

		//! Setzt die Welt-Objekt-ID
		inline void setWorldObjectId(irr::u32 id) { worldObjectId = id; }

	public:

		//! Ermittelt den Physikkörper
		inline physics::PhysicsObject* getPhysicsBody() const {
			return physicsBody;
		}

		//! Setzt den Physikkörper
		inline void setPhysicsBody(physics::PhysicsObject* body) {
			if (body) body->setWorldObject(this);
			physicsBody = body;
		}

		//! Ermittelt den Szenenknoten
		inline nodes::SceneObject* getSceneObject() const {
			return sceneObject;
		}

		//! Setzt das Szenenobjekt
		inline void setSceneObject(nodes::SceneObject* object) {
			sceneObject = object;
		}

		//! Ermittelt die Welt-Objekt-ID
		inline irr::u32 getWorldObjectId() const { return worldObjectId; }

		//! Aktiviert oder deaktiviert die Physik für dieses Objekt
		inline void enablePhysics(bool enable) { physicsBody->setActivationState(enable); }

		//! Aktiviert oder deaktiviert die Physik für dieses Objekt
		inline void setVisibility(bool visible) { sceneObject->setVisibility(visible); }

		//! Versteckt das Objekt und blendet es aus.
		inline void hideAndDisable() {
			physicsBody->setActivationState(false);
			sceneObject->setVisibility(false);
		}

	public:

		//! Wandelt das WorldElement in einen SceneNode um
		inline operator nodes::SceneObject*() const {
			return sceneObject;
		}

		//! Wandelt das WorldElement in einen SceneNode um
		inline operator physics::PhysicsObject*() const {
			return physicsBody;
		}

	private:

		//! Der Physikkörper
		physics::PhysicsObject* physicsBody;

		//! Der Szenenknoten
		nodes::SceneObject* sceneObject;

		//! Die ID des Weltobjektes
		irr::u32 worldObjectId;
	};

}}

#endif