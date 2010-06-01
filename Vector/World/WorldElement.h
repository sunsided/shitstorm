/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _WORLDELEMENT_H
#define _WORLDELEMENT_H

#include "global.h"
#include "Physics/PhysicsObject.h"
#include "SceneNodes/SceneObject.h"

namespace pv {
namespace world {

	//! Ein Element in der Spielwelt
	class WorldElement
	{
	public:

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement(nodes::SceneObject* object = NULL, physics::PhysicsObject* body = NULL);
		
		//! Destruktor
		virtual ~WorldElement(void);
	
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
			if (body) body->setWorldElement(this);
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