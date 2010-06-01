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

namespace pv {
namespace world {

	//! Ein Element in der Spielwelt
	class WorldObject
	{
	public:

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldObject(nodes::SceneObject* object = NULL, physics::PhysicsObject* body = NULL);
		
		//! Destruktor
		virtual ~WorldObject(void);
	
	private:

		//! Kopiert die Translation in den Szenenknoten
		void copyTranslation(const btTransform& startTrans);

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

	};

}}

#endif