/** 
 * Project Vector
 * Physikkörper für Kollisionserkennung
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _COLLISIONDETECTIONPHYSICSOBJECT_H
#define _COLLISIONDETECTIONPHYSICSOBJECT_H

#include "global.h"
#include "PhysicsObject.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace pv {
namespace physics {

	//! Physikkörper
	class CollisionDetectionPhysicsObject
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		CollisionDetectionPhysicsObject(
			PhysicsWorld* physicsWorld = NULL,
			btCollisionShape* collisionShape = NULL,
			world::WorldObject* worldObject = NULL
			) : 
				collisionShape(collisionShape),
				ghostObject(NULL),
				dynamicsWorld(physicsWorld),
				userPointer(worldObject)
		{}

		//! Destruktor
		virtual ~CollisionDetectionPhysicsObject(void);

		//! Initialisiert die Physik
		void initPhysics(f32 ccdThreshold = 1.0f);
		
		//! Setzt die Position des Objektes
		virtual void setPosition(const core::vector3df& v); 

		//! Setzt die Rotation des Objektes
		virtual void setRotation(const core::vector3df& v);

		//! Setzt den Aktivierungszustand
		inline void setActivationState(int state) { ghostObject->setActivationState(state); }

		//! Erzwingt den Aktivierungszustand
		inline void forceActivationState(int state) { ghostObject->forceActivationState(state); }

		//! Ermittelt den Aktivierungszustand
		inline int getActivationState() const { return ghostObject->getActivationState(); }

		//! Setzt die Deaktivierungszeit
		inline void setDeactivationTime(f32 time) { ghostObject->setDeactivationTime(time); }

		//! Setzt die Deaktivierungszeit
		inline f32 getDeactivationTime() const { return ghostObject->getDeactivationTime(); }

		//! Ermittelt die Rotation
		core::vector3df getRotation() const;

		//! Ermittelt die Position
		core::vector3df getPosition() const;

		//! Räumt die Physikgeschichte auf
		void endPhysics(void);
		
	public:

		//! Setzt das Collision Shape
		inline void setCollisionShape(btCollisionShape* shape) { 
			collisionShape = shape; 
			if (ghostObject) ghostObject->setCollisionShape(collisionShape);
		}
		
		//! Ermittelt das Collision Shape
		inline btCollisionShape* getCollisionShape() const { return collisionShape; }

		//! Bezieht den Benutzerzeiger
		inline btGhostObject* getGhostObject() const { return ghostObject; }

		//! Bezieht das Kollisionsobjekt (Rigid Body, ...)
		inline btCollisionObject* getCollisionObject() const { return ghostObject; }

		//! Ermittelt das Motion State
		inline PhysicsWorld* getPhysicsWorld() const { return dynamicsWorld; }

		//! Bezieht den Benutzerzeiger
		inline pv::world::WorldObject* getWorldObject() const { return userPointer; }

	private:

		//! Das Collision Shape
		btCollisionShape* collisionShape;

		//! Der eigentliche Körper
		btGhostObject* ghostObject;

		//! Die Dynamikwelt
		PhysicsWorld* dynamicsWorld;
		
		//! Benutzerdefinierter Zeiger
		pv::world::WorldObject* userPointer;
	};

}}

#endif
