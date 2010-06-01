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
#ifndef _RIGIDPHYSICSBODY_H
#define _RIGIDPHYSICSBODY_H

#include "global.h"
#include "PhysicsBody.h"

namespace pv {
namespace physics {

	//! Physikkörper
	class RigidPhysicsBody : public PhysicsBody
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		RigidPhysicsBody(
			PhysicsMotionState* state = NULL,
			f32 mass = 0.0f,
			PhysicsWorld* physicsWorld = NULL,
			btCollisionShape* collisionShape = NULL
			) : 
				PhysicsBody(state, mass, physicsWorld, collisionShape),
				mass(mass),
				rigidBody(NULL)
		{}

		//! Destruktor
		virtual ~RigidPhysicsBody(void);

		//! Initialisiert die Physik
		void initPhysics(f32 ccdThreshold = 1.0f, f32 linearDamping = 0.f, f32 angularDamping = 0.f, f32 friction = 0.5f, f32 restitution = 0.f);
		
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

	public:

		//! Bezieht den Benutzerzeiger
		inline btRigidBody* getRigidBody() const { return rigidBody; }

		//! Bezieht das Kollisionsobjekt (Rigid Body, ...)
		inline btCollisionObject* getCollisionObject() const { return rigidBody; }

	private:

		//! Die Masse des Körpers
		irr::f32 mass;

		//! Der eigentliche Körper
		btRigidBody* rigidBody;
	};

}}

#endif
