/** 
 * Project Vector
 * Physikkörper
 *
 * Kudos an: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=17910
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSOBJECT_H
#define _PHYSICSOBJECT_H

#include "global.h"
#include "PhysicsMotionState.h"
#include "IrrBtConversion.h"
#include <btBulletDynamicsCommon.h>

using namespace irr;

// Vorwärtsdeklaration
namespace pv {
	namespace world {
		class WorldObject;
	}
}

namespace pv {
namespace physics {

	// Vorwärtsdeklaration der Klassen
	class PhysicsWorld;

	//! Physikkörper
	class PhysicsObject
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		PhysicsObject(
			PhysicsMotionState* state = NULL,
			PhysicsWorld* physicsWorld = NULL,
			btCollisionShape* collisionShape = NULL,
			world::WorldObject* worldObject = NULL
			) : 
			motionState(state), 
			dynamicsWorld(physicsWorld), 
			collisionShape(collisionShape),
			userPointer(worldObject)
		{}

		//! Destruktor
		virtual ~PhysicsObject(void);

		//! Initialisiert die Physik
		virtual void initPhysics(f32 ccdThreshold = 1.0f, f32 linearDamping = 0.f, f32 angularDamping = 0.f, f32 friction = 0.5f, f32 restitution = 0.f) = 0;
		
		//! Setzt die Position des Objektes
		virtual void setPosition(const core::vector3df& v) = 0;

		//! Setzt die Rotation des Objektes
		virtual void setRotation(const core::vector3df& v)  = 0;

		//! Ermittelt die lineare Geschwindigkeit
		virtual core::vector3df getLinearVelocity() const = 0;

		//! Setzt die lineare Geschwindigkeit
		virtual void setLinearVelocity(const core::vector3df& vel) = 0;

		//! Ermittelt die Winkelgeschwindigkeit
		virtual core::vector3df getAngularVelocity() const = 0;

		//! Setzt die Winkelgeschwindigkeit
		virtual void setAngularVelocity(const core::vector3df& vel) = 0;
		
		//! Wendet eine Kraft auf das Objekt an
		virtual void applyForce(const core::vector3df& v) = 0;

		//! Setzt alle Kräfte zurück
		virtual void zeroForces() = 0;

		//! Setzt den Aktivierungszustand
		inline void setActivationStateC(const int& active) { setActivationState(active); }

		//! Setzt den Aktivierungszustand
		virtual void setActivationState(int active) = 0;

		//! Erzwingt den Aktivierungszustand
		virtual void forceActivationState(int active) = 0;

		//! Ermittelt den Aktivierungszustand
		virtual int getActivationState() const = 0;

		//! Setzt den Aktivierungszustand auf ACTIVE_TAG
		inline void makeActive() { forceActivationState(ACTIVE_TAG); }

		//! Setzt den Aktivierungszustand
		inline void setSimulationEnabled(const bool& active) { 
			switch(active) {
			case true:	forceActivationState(ACTIVE_TAG); setDeactivationTime(0.0f); return;
			case false:	setActivationState(DISABLE_SIMULATION); return;
			}
		}

		//! Ermittelt den Aktivierungszustand
		inline bool getSimulationEnabled() const { return getActivationState() != DISABLE_SIMULATION; }

		//! Setzt die Deaktivierungszeit
		virtual void setDeactivationTime(f32 time) = 0;

		//! Setzt die Deaktivierungszeit
		virtual f32 getDeactivationTime() const = 0;

		//! Ermittelt die Rotation
		virtual core::vector3df getRotation() const = 0;

		//! Ermittelt die Position
		virtual core::vector3df getPosition() const = 0;

		//! Räumt die Physikgeschichte auf
		virtual void endPhysics(void);

		//! Ermittelt, ob das Objekt statisch ist
		inline bool isStatic() const { return getMass() == 0.0f; }

		//! Ermittelt die Masse des Objektes
		virtual f32 getMass() const = 0;

		//! Aktualisiert die Masse des Objektes
		virtual void updateMass(f32 mass) = 0;

		//! Aktualisiert die Masse des Objektes
		virtual void updateMass(f32 mass, const btVector3& localInertia) = 0;

		//! Aktualisiert die Masse des Objektes
		inline void updateMass(f32 mass, const irr::core::vector3df& localInertia) {
			btVector3 inertia = conversion::toBulletVector(localInertia);
			updateMass(mass, inertia);
		}

		//! Ermittelt, ob es sich um einen Festkörper handelt
		virtual bool isRigidBody() const = 0;

		//! Gibt sich selbst als Rigid Body zurück
		virtual btRigidBody* getAsRigidBody() = 0;

	public:

		//! Setzt das Collision Shape
		inline void setCollisionShape(btCollisionShape* shape) { collisionShape = shape; }

		//! Ermittelt das Collision Shape
		inline btCollisionShape* getCollisionShape() const { return collisionShape; }

		//! Setzt das Motion State
		inline void setMotionState(PhysicsMotionState* state) { motionState = state; }

		//! Ermittelt das Motion State
		inline PhysicsMotionState* getMotionState() const { return motionState; }

		//! Bezieht den Benutzerzeiger
		inline pv::world::WorldObject* getWorldObject() const { return userPointer; }

		//! Bezieht den Benutzerzeiger
		inline void setWorldObject(pv::world::WorldObject* world) { userPointer = world; }

		//! Bezieht das Kollisionsobjekt (Rigid Body, ...)
		inline virtual btCollisionObject* getCollisionObject() const = 0;

		//! Ermittelt das Motion State
		inline PhysicsWorld* getPhysicsWorld() const { return dynamicsWorld; }

	public:

		//! Wandelt einen Quaternion in einen Euler-Rotationsvektor um
		static void QuaternionToEulerXYZ(const btQuaternion &quat, btVector3 &euler);

		//! Wandelt einen Euler-Rotationsvektor in einen Quaternion um
		static void EulerXYZToQuaternion(btVector3 &euler, btQuaternion &quat);

		//! Bezieht ein Bullet-Mesh aus einem Irrlicht-Mesh
		static btTriangleMesh* GetTriangleMesh(scene::IMesh* pIMesh);

	private:

		//! Das Collision Shape
		btCollisionShape* collisionShape;

		//! Die Dynamikwelt
		PhysicsWorld* dynamicsWorld;

		//! Der Motion State
		PhysicsMotionState* motionState;
		
		//! Benutzerdefinierter Zeiger
		pv::world::WorldObject* userPointer;
	};

}}

#endif
