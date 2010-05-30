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
#ifndef _PHYSICSBODY_H
#define _PHYSICSBODY_H

#include "global.h"
#include "PhysicsMotionState.h"

#include <btBulletDynamicsCommon.h>

using namespace irr;

namespace pv {
namespace physics {

	// Vorwärtsdeklaration der Klassen
	class PhysicsWorld;

	//! Physikkörper
	class PhysicsBody : public PhysicsMotionState
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		PhysicsBody(
			const btTransform& startTrans = btTransform::getIdentity(), 
			const btTransform& centerOfMassOffset = btTransform::getIdentity(),
			f32 mass = 0.0f,
			PhysicsWorld* physicsWorld = NULL,
			btCollisionShape* collisionShape = NULL
			) 
			: PhysicsMotionState(startTrans, centerOfMassOffset), 
			dynamicsWorld(physicsWorld), mass(mass), collisionShape(collisionShape)
		{}

		//! Erzeugt eine neue Instanz des Objektes
		PhysicsBody(
			const core::matrix4& startTrans, 
			const core::matrix4& centerOfMassOffset,
			f32 mass = 0.0f,
			PhysicsWorld* physicsWorld = NULL,
			btCollisionShape* collisionShape = NULL
			) 
			: PhysicsMotionState(conversion::toBtTransform(startTrans), conversion::toBtTransform(centerOfMassOffset)) ,
			dynamicsWorld(physicsWorld), mass(mass), collisionShape(collisionShape)
		{}

		//! Destruktor
		virtual ~PhysicsBody(void);

		//! Initialisiert die Physik
		void initPhysics(f32 ccdThreshold, f32 linearDamping = 0.f, f32 angularDamping = 0.f, f32 friction = 0.5f, f32 restitution = 0.f);
		
		//! Setzt die Position des Objektes
		virtual void setPosition(const core::vector3df& v); 

		//! Setzt die Rotation des Objektes
		virtual void setRotation(const core::vector3df& v);

		//! Ermittelt die lineare Geschwindigkeit
		core::vector3df getLinearVelocity() const;

		//! Setzt die lineare Geschwindigkeit
		void setLinearVelocity(const core::vector3df& vel) const;

		//! Ermittelt die Winkelgeschwindigkeit
		core::vector3df getAngularVelocity() const;

		//! Setzt die Winkelgeschwindigkeit
		void setAngularVelocity(const core::vector3df& vel) const;
		
		//! Wendet eine Kraft auf das Objekt an
		void applyForce(const core::vector3df& v);

		//! Setzt alle Kräfte zurück
		void zeroForces();

		//! Setzt den Aktivierungszustand
		void setActivationState(bool active);

		//! Ermittelt die Rotation
		core::vector3df getRotation() const;

		//! Ermittelt die Position
		core::vector3df getPosition() const;

		//! Räumt die Physikgeschichte auf
		void endPhysics(void);

		//! Aktualisiert die Masse des Objektes
		void updateMass(f32 mass);

		//! Aktualisiert die Masse des Objektes
		void updateMass(f32 mass, const btVector3& localInertia);

	protected:

		//! Setzt das Collision Shape
		inline void setCollisionShape(btCollisionShape* shape) { collisionShape = shape; }

		//! Ermittelt das Collision Shape
		inline btCollisionShape* getCollisionShape() const { return collisionShape; }

		//! Wandelt einen Quaternion in einen Euler-Rotationsvektor um
		static void QuaternionToEulerXYZ(const btQuaternion &quat, btVector3 &euler);

		//! Wandelt einen Euler-Rotationsvektor in einen Quaternion um
		static void EulerXYZToQuaternion(btVector3 &euler, btQuaternion &quat);

		//! Bezieht ein Bullet-Mesh aus einem Irrlicht-Mesh
		static btTriangleMesh* GetTriangleMesh(scene::IMesh* pIMesh);

	private:

		//! Die Masse des Körpers
		irr::f32 mass;

		//! Das Collision Shape
		btCollisionShape* collisionShape;

		//! Der eigentliche Körper
		btRigidBody* rigidBody;

		//! Die Dynamikwelt
		PhysicsWorld* dynamicsWorld;
	};

}}

#endif
