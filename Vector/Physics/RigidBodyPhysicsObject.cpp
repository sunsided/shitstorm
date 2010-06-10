/** 
 * Project Vector
 * Physikkörper
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "RigidBodyPhysicsObject.h"
#include "PhysicsWorld.h"

// 360 / (2*PI)
#ifndef GRAD_PI 
#define GRAD_PI 57.29577951f
#endif

#ifndef GRAD_PI2
#define GRAD_PI2 0.0174532925f
#endif

namespace pv {
namespace physics {

	//! Destruktor
	RigidBodyPhysicsObject::~RigidBodyPhysicsObject(void) {
		endPhysics();
	}

	//! Beendet die Physikgeschichte
	void RigidBodyPhysicsObject::endPhysics(void)
	{
		if (getPhysicsWorld()) getPhysicsWorld()->removeObject(this);
		if (rigidBody) {
			delete rigidBody;
			rigidBody = NULL;
		}
		
		// Durchreichen
		PhysicsObject::endPhysics();
	}

	//! Aktualisiert die Masse des Objektes
	void RigidBodyPhysicsObject::updateMass(f32 newMass) {
		if (!getCollisionShape() || !rigidBody) {
			mass = newMass;
			return;
		}
		
		// Lokale Trägheit berechnen
		mass = newMass;
		btVector3 localInertia(0, 0, 0);
		if (newMass != 0) getCollisionShape()->calculateLocalInertia(newMass, localInertia);
		rigidBody->setMassProps(mass, localInertia);
	}

	//! Aktualisiert die Masse des Objektes
	void RigidBodyPhysicsObject::updateMass(f32 newMass, const btVector3& localInertia) {
		if (!rigidBody) {
			mass = newMass;
			return;
		}
		
		// Lokale Trägheit berechnen
		mass = newMass;
		rigidBody->setMassProps(mass, localInertia);
	}

	// Physik initialisieren
	void RigidBodyPhysicsObject::initPhysics(f32 ccdThreshold, f32 linearDamping, f32 angularDamping, f32 friction, f32 restitution)
	{
		ASSERT(getCollisionShape());
		ASSERT(getPhysicsWorld());

		// Lokale Trägheit berechnen
		btVector3 localInertia(0, 0, 0);
		if (mass != 0) getCollisionShape()->calculateLocalInertia(mass, localInertia);

		// Körper erzeugen
		btRigidBody::btRigidBodyConstructionInfo info(mass, getMotionState(), getCollisionShape(), localInertia);
		info.m_angularDamping = angularDamping;
		info.m_friction = friction;
		info.m_restitution = restitution;
		info.m_linearDamping = linearDamping;
		info.m_startWorldTransform = getMotionState()->m_startWorldTrans;

		rigidBody = new btRigidBody(info);
		rigidBody->setUserPointer((void*)this);

		// Parameter für Continous Collision Detection setzen
		rigidBody->setCcdMotionThreshold( ccdThreshold );
		rigidBody->setCcdSweptSphereRadius( 0.2f*ccdThreshold ); // TODO: Parameter herausziehen
	}

	//! Setzt die Position
	void RigidBodyPhysicsObject::setPosition(const core::vector3df &v) {
		if (!rigidBody) return;

		// Welttransformation des Körpers neu setzen
		btTransform t=rigidBody->getWorldTransform();
		btVector3 btv(v.X, v.Y, v.Z);
		t.setOrigin(btv);
		rigidBody->setWorldTransform(t);

		//if (rigidBody->getActivationState()==ISLAND_SLEEPING) {
		//	OutputDebugString("deactivated ");
		//}
	}

	//! Bezieht die Position
	core::vector3df RigidBodyPhysicsObject::getPosition() const {
		if (!rigidBody) return core::vector3df(0, 0, 0);
		btVector3 p = rigidBody->getCenterOfMassPosition();
		return core::vector3df(p.getX(), p.getY(), p.getZ());
	}

	//! Setzt die Rotation
	void RigidBodyPhysicsObject::setRotation(const core::vector3df &v) {
		if (!rigidBody) return;

		btTransform t=rigidBody->getWorldTransform();
		btQuaternion btq;
		EulerXYZToQuaternion(btVector3(v.X * GRAD_PI2, v.Y * GRAD_PI2, v.Z * GRAD_PI2), btq);
		t.setRotation(btq);
		rigidBody->setWorldTransform(t);
	}

	//! Bezieht die Rotation
	core::vector3df RigidBodyPhysicsObject::getRotation() const {
		if (!rigidBody) return core::vector3df(0,0,0);

		btVector3 btv;
		btQuaternion btq = rigidBody->getOrientation();
		QuaternionToEulerXYZ(btq, btv);
 		core::vector3df v(btv.getX(), btv.getY(), btv.getZ());
		v *= GRAD_PI;
		return v;
	}

	//! Bezieht die lineare Geschwindigkeit
	core::vector3df RigidBodyPhysicsObject::getLinearVelocity() const {	
		if (!rigidBody || mass == 0) return core::vector3df(0,0,0);

		btVector3 btV = rigidBody->getLinearVelocity();
		return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
	}

	//! Setzt die lineare Geschwindigkeit
	void RigidBodyPhysicsObject::setLinearVelocity(const core::vector3df & vel) {	
		if (!rigidBody || mass == 0) return; //bullet hangs if attempt to set lin. or ang. velocity on static object
		rigidBody->setLinearVelocity(btVector3(vel.X, vel.Y, vel.Z));
		
		//note - apparently, need to use motion state on kinematic objects, and rigid body functions
		// on dynamic rigid bodies to change pos / rot etc.
	}

	//! Ermittelt die Winkelgeschwindigkeit
	core::vector3df RigidBodyPhysicsObject::getAngularVelocity() const {	
		if (!rigidBody || mass == 0) return core::vector3df(0,0,0);
		btVector3 btV = rigidBody->getAngularVelocity();
		return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
	}

	//! Setzt die Winkelgeschwindigkeit
	void RigidBodyPhysicsObject::setAngularVelocity(const core::vector3df & vel) {	
		if (!rigidBody || mass == 0) return;
		rigidBody->setAngularVelocity(btVector3(vel.X, vel.Y, vel.Z));
	}

	//! Wendet eine Kraft auf den Körper an
	void RigidBodyPhysicsObject::applyForce(const core::vector3df &v) {
		if (!rigidBody) return;
		rigidBody->applyForce(btVector3(v.X, v.Y, v.Z), btVector3(0,0,0));
	}

	//! Setzt alle Kräfte zurück
	void RigidBodyPhysicsObject::zeroForces() {
		if (!rigidBody) return;
		rigidBody->setLinearVelocity(btVector3(0,0,0));
		rigidBody->setAngularVelocity(btVector3(0,0,0));
	}

}}
