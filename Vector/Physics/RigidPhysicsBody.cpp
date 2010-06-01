/** 
 * Project Vector
 * Physikkörper
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "RigidPhysicsBody.h"
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
	RigidPhysicsBody::~RigidPhysicsBody(void) {
		endPhysics();
	}

	//! Beendet die Physikgeschichte
	void RigidPhysicsBody::endPhysics(void)
	{
		if (dynamicsWorld) dynamicsWorld->removeBody(this);
		if (rigidBody) {
			delete rigidBody;
			rigidBody = NULL;
		}

		if (motionState) {
			delete motionState;
			motionState = NULL;
		}

		//TODO: Collision Shape-Referenzzähler
		//g_pCollisionObjectMgr->Remove(m_pCollisionObject);
	}

	//! Aktualisiert die Masse des Objektes
	void RigidPhysicsBody::updateMass(f32 newMass) {
		if (!collisionShape || !rigidBody) {
			mass = newMass;
			return;
		}
		
		// Lokale Trägheit berechnen
		mass = newMass;
		btVector3 localInertia(0, 0, 0);
		if (newMass != 0) collisionShape->calculateLocalInertia(newMass, localInertia);
		rigidBody->setMassProps(mass, localInertia);
	}

	//! Aktualisiert die Masse des Objektes
	void RigidPhysicsBody::updateMass(f32 newMass, const btVector3& localInertia) {
		if (!collisionShape || !rigidBody) {
			mass = newMass;
			return;
		}
		
		// Lokale Trägheit berechnen
		mass = newMass;
		rigidBody->setMassProps(mass, localInertia);
	}

	// Physik initialisieren
	void RigidPhysicsBody::initPhysics(f32 ccdThreshold, f32 linearDamping, f32 angularDamping, f32 friction, f32 restitution)
	{
		ASSERT(collisionShape);
		ASSERT(dynamicsWorld);

		// Lokale Trägheit berechnen
		btVector3 localInertia(0, 0, 0);
		if (mass != 0) collisionShape->calculateLocalInertia(mass, localInertia);

		// Körper erzeugen
		btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, collisionShape, localInertia);
		info.m_angularDamping = angularDamping;
		info.m_friction = friction;
		info.m_restitution = restitution;
		info.m_linearDamping = linearDamping;
		info.m_startWorldTransform = motionState->m_startWorldTrans;

		rigidBody = new btRigidBody(info);
		rigidBody->setUserPointer((void*)this);

		// CCD-Parameter setzen
		// TODO: Was passiert hier eigentlich? Ich hab das hierher: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=17910
		rigidBody->setCcdMotionThreshold( ccdThreshold );
		rigidBody->setCcdSweptSphereRadius( 0.2f*ccdThreshold );
	}

	//! Setzt die Position
	void RigidPhysicsBody::setPosition(const core::vector3df &v) {
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
	core::vector3df RigidPhysicsBody::getPosition() const {
		if (!rigidBody) return core::vector3df(0, 0, 0);
		btVector3 p = rigidBody->getCenterOfMassPosition();
		return core::vector3df(p.getX(), p.getY(), p.getZ());
	}

	//! Setzt die Rotation
	void RigidPhysicsBody::setRotation(const core::vector3df &v) {
		if (!rigidBody) return;

		btTransform t=rigidBody->getWorldTransform();
		btQuaternion btq;
		EulerXYZToQuaternion(btVector3(v.X * GRAD_PI2, v.Y * GRAD_PI2, v.Z * GRAD_PI2), btq);
		t.setRotation(btq);
		rigidBody->setWorldTransform(t);
	}

	//! Bezieht die Rotation
	core::vector3df RigidPhysicsBody::getRotation() const {
		if (!rigidBody) return core::vector3df(0,0,0);

		btVector3 btv;
		btQuaternion btq = rigidBody->getOrientation();
		QuaternionToEulerXYZ(btq, btv);
 		core::vector3df v(btv.getX(), btv.getY(), btv.getZ());
		v *= GRAD_PI;
		return v;
	}

	//! Bezieht die lineare Geschwindigkeit
	core::vector3df RigidPhysicsBody::getLinearVelocity() const {	
		if (!rigidBody || mass==0) return core::vector3df(0,0,0);

		btVector3 btV = rigidBody->getLinearVelocity();
		return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
	}

	//! Setzt die lineare Geschwindigkeit
	void RigidPhysicsBody::setLinearVelocity(const core::vector3df & vel) const {	
		if (!rigidBody || mass==0) return; //bullet hangs if attempt to set lin. or ang. velocity on static object
		rigidBody->setLinearVelocity(btVector3(vel.X, vel.Y, vel.Z));
		//note - apparently, need to use motion state on kinematic objects, and rigid body functions
		// on dynamic rigid bodies to change pos / rot etc.
	}

	//! Ermittelt die Winkelgeschwindigkeit
	core::vector3df RigidPhysicsBody::getAngularVelocity() const {	
		if (!rigidBody || mass == 0) return core::vector3df(0,0,0);
		btVector3 btV = rigidBody->getAngularVelocity();
		return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
	}

	//! Setzt die Winkelgeschwindigkeit
	void RigidPhysicsBody::setAngularVelocity(const core::vector3df & vel) const {	
		if (!rigidBody || mass == 0) return;
		rigidBody->setAngularVelocity(btVector3(vel.X, vel.Y, vel.Z));
	}

	//! Wendet eine Kraft auf den Körper an
	void RigidPhysicsBody::applyForce(const core::vector3df &v) {
		if (!rigidBody) return;
		rigidBody->applyForce(btVector3(v.X, v.Y, v.Z), btVector3(0,0,0));
	}

	//! Setzt alle Kräfte zurück
	void RigidPhysicsBody::zeroForces() {
		if (!rigidBody) return;
		rigidBody->setLinearVelocity(btVector3(0,0,0));
		rigidBody->setAngularVelocity(btVector3(0,0,0));
	}

}}
