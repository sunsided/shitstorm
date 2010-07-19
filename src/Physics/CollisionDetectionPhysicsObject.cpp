/** 
 * Project Vector
 * Physikkörper für Kollisionserkennung
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "CollisionDetectionPhysicsObject.h"
#include "PhysicsWorld.h"

namespace pv {
namespace physics {

	//! Destruktor
	CollisionDetectionPhysicsObject::~CollisionDetectionPhysicsObject(void) {
		endPhysics();
	}

	//! Beendet die Physikgeschichte
	void CollisionDetectionPhysicsObject::endPhysics(void)
	{
		if (getPhysicsWorld()) getPhysicsWorld()->removeObject(this);
		if (ghostObject) {
			delete ghostObject;
			ghostObject = NULL;
		}

		
	}
	
	// Physik initialisieren
	void CollisionDetectionPhysicsObject::initPhysics(f32 ccdThreshold)
	{
		ASSERT(getPhysicsWorld());
		
		// Körper erzeugen
		ghostObject = new btPairCachingGhostObject();
		ghostObject->setCollisionShape(collisionShape);
		ghostObject->setUserPointer((void*)this);

		// Parameter für Continous Collision Detection setzen
		ghostObject->setCcdMotionThreshold( ccdThreshold );
		ghostObject->setCcdSweptSphereRadius( 0.2f*ccdThreshold ); // TODO: Parameter herausziehen
	}

	//! Setzt die Position
	void CollisionDetectionPhysicsObject::setPosition(const core::vector3df &v) {
		if (!ghostObject) return;

		// Welttransformation des Körpers neu setzen
		btTransform t=ghostObject->getWorldTransform();
		btVector3 btv(v.X, v.Y, v.Z);
		t.setOrigin(btv);
		ghostObject->setWorldTransform(t);

		//if (rigidBody->getActivationState()==ISLAND_SLEEPING) {
		//	OutputDebugString("deactivated ");
		//}
	}

	//! Bezieht die Position
	core::vector3df CollisionDetectionPhysicsObject::getPosition() const {
		if (!ghostObject) return core::vector3df(0, 0, 0);
		
		btTransform transform = ghostObject->getWorldTransform();
		btVector3 origin = transform.getOrigin();

		return conversion::toIrrlichtVector(origin);
	}

	//! Setzt die Rotation
	void CollisionDetectionPhysicsObject::setRotation(const core::vector3df &v) {
		if (!ghostObject) return;

		btTransform t=ghostObject->getWorldTransform();
		btQuaternion btq;

		btVector3 vec = conversion::toBulletVector(v) * (btScalar)INV_GRAD_PI;

		PhysicsObject::EulerXYZToQuaternion(vec, btq);
		t.setRotation(btq);
		ghostObject->setWorldTransform(t);
	}

	//! Bezieht die Rotation
	core::vector3df CollisionDetectionPhysicsObject::getRotation() const {
		if (!ghostObject) return core::vector3df(0,0,0);

		// Rotation holen
		btTransform transform = ghostObject->getWorldTransform();
		btQuaternion btq = transform.getRotation();

		// Rotation konvertieren
		btVector3 btv;
		PhysicsObject::QuaternionToEulerXYZ(btq, btv);
 		core::vector3df v(btv.getX(), btv.getY(), btv.getZ());
		v *= (irr::f32)GRAD_PI;
		return v;
	}
	
}}
