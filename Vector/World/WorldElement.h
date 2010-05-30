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
	class WorldElement : protected physics::PhysicsBody, protected irr::scene::ISceneNode
	{
	protected:
		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id=-1,
				const btTransform& startTrans = btTransform::getIdentity(), 
				const btTransform& centerOfMassOffset = btTransform::getIdentity(),
				f32 mass = 0.0f,
				physics::PhysicsWorld* physicsWorld = NULL,
				btCollisionShape* collisionShape = NULL
				);

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement(irr::scene::ISceneNode& node, physics::PhysicsBody& body);
		
		//! Destruktor
		virtual ~WorldElement(void) {}

	protected:

		//! Aktualisiert die Welttransformation.
		/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
		 * @param worldTrans	Die zu setzende Transformation
		 */
		virtual void setWorldTransform(const btTransform& worldTrans);

	};

}}

#endif