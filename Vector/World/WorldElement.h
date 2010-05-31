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
#include "Physics/PhysicsBody.h"

namespace pv {
namespace world {

	//! Ein Element in der Spielwelt
	class WorldElement
	{
	protected:
		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement(scene::ISceneNode* node,
				const btTransform& startTrans = btTransform::getIdentity(), 
				const btTransform& centerOfMassOffset = btTransform::getIdentity(),
				f32 mass = 0.0f,
				physics::PhysicsWorld* physicsWorld = NULL,
				btCollisionShape* collisionShape = NULL
				);

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement(scene::ISceneNode* node = NULL, physics::PhysicsBody* body = NULL);
		
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
		inline operator physics::PhysicsBody*() const {
			return physicsBody;
		}

		//! Ermittelt den Physikkörper
		inline physics::PhysicsBody* getPhysicsBody() const {
			return physicsBody;
		}

		//! Ermittelt den Szenenknoten
		inline irr::scene::ISceneNode* getSceneNode() const {
			return sceneNode;
		}

		//! Setzt den Physikkörper
		inline void setPhysicsBody(physics::PhysicsBody* body) {
			if (body) body->setWorldElement(this);
			physicsBody = body;
		}

		//! Setzt den Szenenknoten
		inline void setSceneNode(irr::scene::ISceneNode* node) {
			sceneNode = node;
		}

	private:

		//! Der Physikkörper
		physics::PhysicsBody* physicsBody;

		//! Der Szenenknoten
		irr::scene::ISceneNode* sceneNode;

	};

}}

#endif