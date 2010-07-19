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
	class CollisionDetectionPhysicsObject : public PhysicsObject
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		CollisionDetectionPhysicsObject(
			PhysicsMotionState* state = NULL,
			f32 mass = 0.0f,
			PhysicsWorld* physicsWorld = NULL,
			btCollisionShape* collisionShape = NULL,
			world::WorldObject* worldObject = NULL
			) : 
				PhysicsObject(state, physicsWorld, collisionShape, worldObject),
				mass(mass),
				ghostObject(NULL)
		{}

		//! Destruktor
		virtual ~CollisionDetectionPhysicsObject(void);

		//! Initialisiert die Physik
		void initPhysics(f32 ccdThreshold = 1.0f, f32 = 0.f, f32 = 0.f, f32 = 0.5f, f32 = 0.f);
		
		//! Setzt die Position des Objektes
		virtual void setPosition(const core::vector3df& v); 

		//! Setzt die Rotation des Objektes
		virtual void setRotation(const core::vector3df& v);

		//! Ermittelt die lineare Geschwindigkeit
		inline core::vector3df getLinearVelocity() const { return core::vector3df(0, 0, 0); }

		//! Setzt die lineare Geschwindigkeit
		inline void setLinearVelocity(const core::vector3df& vel) {}

		//! Ermittelt die Winkelgeschwindigkeit
		inline core::vector3df getAngularVelocity() const { return core::vector3df(0, 0, 0); }

		//! Setzt die Winkelgeschwindigkeit
		inline void setAngularVelocity(const core::vector3df& vel) {}
		
		//! Wendet eine Kraft auf das Objekt an
		inline void applyForce(const core::vector3df& v) {}

		//! Setzt alle Kräfte zurück
		inline void zeroForces() {}

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

		//! Ermittelt die Masse des Objektes
		inline f32 getMass() const { return 0.0f; }

		//! Aktualisiert die Masse des Objektes
		inline void updateMass(f32 mass) {}

		//! Aktualisiert die Masse des Objektes
		inline void updateMass(f32 mass, const btVector3& localInertia) {}

		//! Ermittelt, ob es sich um einen Festkörper handelt
		inline bool isRigidBody() const { return false; }
		
		//! Ermittelt, ob es sich um einen Geistobjekt handelt
		inline bool isGhostObject() const { return true; }

		//! Gibt sich selbst als Rigid Body zurück
		inline btRigidBody* getAsRigidBody() { return NULL; }

		//! Ermittelt den Gravitationsvektor
		inline core::vector3df getGravity() const { return core::vector3df(0, 0, 0); }

		//! Aktualisiert den Gravitationsvektor des Objektes
		inline void setGravity(const btVector3& gravity) {}

	public:

		//! Bezieht den Benutzerzeiger
		inline btGhostObject* getGhostObject() const { return ghostObject; }

		//! Bezieht das Kollisionsobjekt (Rigid Body, ...)
		inline btCollisionObject* getCollisionObject() const { return ghostObject; }

	private:

		//! Die Masse des Körpers
		irr::f32 mass;

		//! Der eigentliche Körper
		btGhostObject* ghostObject;
	};

}}

#endif
