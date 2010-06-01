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

namespace pv {
namespace world {

	//! Ein Element in der Spielwelt
	class WorldElement
	{
	public:

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement(scene::ISceneNode* node = NULL, physics::PhysicsObject* body = NULL);
		
		//! Destruktor
		virtual ~WorldElement(void);
	
	private:

		//! Kopiert die Translation in den Szenenknoten
		void copyTranslation(const btTransform& startTrans);

	public:

		//! Wandelt das WorldElement in einen SceneNode um
		inline operator irr::scene::ISceneNode*() const {
			return sceneNode;
		}

		//! Wandelt das WorldElement in einen SceneNode um
		inline operator physics::PhysicsObject*() const {
			return physicsBody;
		}

		//! Ermittelt den Physikkörper
		inline physics::PhysicsObject* getPhysicsBody() const {
			return physicsBody;
		}

		//! Ermittelt den Szenenknoten
		inline irr::scene::ISceneNode* getSceneNode() const {
			return sceneNode;
		}

		//! Setzt den Physikkörper
		inline void setPhysicsBody(physics::PhysicsObject* body) {
			if (body) body->setWorldElement(this);
			physicsBody = body;
		}

		//! Setzt den Szenenknoten
		inline void setSceneNode(irr::scene::ISceneNode* node) {
			sceneNode = node;
		}

	private:

		//! Der Physikkörper
		physics::PhysicsObject* physicsBody;

		//! Der Szenenknoten
		irr::scene::ISceneNode* sceneNode;

	};

}}

#endif