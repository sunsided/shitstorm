/** 
 * Project Vector
 * Physikkörper
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsBody.h"
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
	PhysicsBody::~PhysicsBody(void) {
		endPhysics();
	}

	//! Beendet die Physikgeschichte
	void PhysicsBody::endPhysics(void)
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
	void PhysicsBody::updateMass(f32 newMass) {
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
	void PhysicsBody::updateMass(f32 newMass, const btVector3& localInertia) {
		if (!collisionShape || !rigidBody) {
			mass = newMass;
			return;
		}
		
		// Lokale Trägheit berechnen
		mass = newMass;
		rigidBody->setMassProps(mass, localInertia);
	}

	// Physik initialisieren
	void PhysicsBody::initPhysics(f32 ccdThreshold, f32 linearDamping, f32 angularDamping, f32 friction, f32 restitution)
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

		// Den Körper zur Welt hinzufügen
		// dynamicsWorld->addBody(rigidBody);

		// Werte zurücksetzen
		setPosition(core::vector3df(0, 0, 0));
		setRotation(core::vector3df(0, 0, 0));
	
		// CCD-Parameter setzen
		// TODO: Was passiert hier eigentlich? Ich hab das hierher: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=17910
		rigidBody->setCcdMotionThreshold( ccdThreshold );
		rigidBody->setCcdSweptSphereRadius( 0.2f*ccdThreshold );
	}

	//! Setzt die Position
	void PhysicsBody::setPosition(const core::vector3df &v) {
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
	core::vector3df PhysicsBody::getPosition() const {
		if (!rigidBody) return core::vector3df(0, 0, 0);
		btVector3 p = rigidBody->getCenterOfMassPosition();
		return core::vector3df(p.getX(), p.getY(), p.getZ());
	}

	//! Setzt die Rotation
	void PhysicsBody::setRotation(const core::vector3df &v) {
		if (!rigidBody) return;

		btTransform t=rigidBody->getWorldTransform();
		btQuaternion btq;
		EulerXYZToQuaternion(btVector3(v.X * GRAD_PI2, v.Y * GRAD_PI2, v.Z * GRAD_PI2), btq);
		t.setRotation(btq);
		rigidBody->setWorldTransform(t);
	}

	//! Bezieht die Rotation
	core::vector3df PhysicsBody::getRotation() const {
		if (!rigidBody) return core::vector3df(0,0,0);

		btVector3 btv;
		btQuaternion btq = rigidBody->getOrientation();
		QuaternionToEulerXYZ(btq, btv);
 		core::vector3df v(btv.getX(), btv.getY(), btv.getZ());
		v *= GRAD_PI;
		return v;
	}

	//! Bezieht die lineare Geschwindigkeit
	core::vector3df PhysicsBody::getLinearVelocity() const {	
		if (!rigidBody || mass==0) return core::vector3df(0,0,0);

		btVector3 btV = rigidBody->getLinearVelocity();
		return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
	}

	//! Setzt die lineare Geschwindigkeit
	void PhysicsBody::setLinearVelocity(const core::vector3df & vel) const {	
		if (!rigidBody || mass==0) return; //bullet hangs if attempt to set lin. or ang. velocity on static object
		rigidBody->setLinearVelocity(btVector3(vel.X, vel.Y, vel.Z));
		//note - apparently, need to use motion state on kinematic objects, and rigid body functions
		// on dynamic rigid bodies to change pos / rot etc.
	}

	//! Ermittelt die Winkelgeschwindigkeit
	core::vector3df PhysicsBody::getAngularVelocity() const {	
		if (!rigidBody || mass == 0) return core::vector3df(0,0,0);
		btVector3 btV = rigidBody->getAngularVelocity();
		return core::vector3df(btV.getX(), btV.getY(), btV.getZ());
	}

	//! Setzt die Winkelgeschwindigkeit
	void PhysicsBody::setAngularVelocity(const core::vector3df & vel) const {	
		if (!rigidBody || mass == 0) return;
		rigidBody->setAngularVelocity(btVector3(vel.X, vel.Y, vel.Z));
	}

	//! Wendet eine Kraft auf den Körper an
	void PhysicsBody::applyForce(const core::vector3df &v) {
		if (!rigidBody) return;
		rigidBody->applyForce(btVector3(v.X, v.Y, v.Z), btVector3(0,0,0));
	}

	//! Setzt alle Kräfte zurück
	void PhysicsBody::zeroForces() {
		if (!rigidBody) return;
		rigidBody->setLinearVelocity(btVector3(0,0,0));
		rigidBody->setAngularVelocity(btVector3(0,0,0));
	}

	//! Wandelt einen Quaternion in einen Euler-Rotationsvektor um
	void PhysicsBody::QuaternionToEulerXYZ(const btQuaternion &quat,btVector3 &euler) {
		f32 w = quat.getW();	
		f32 x = quat.getX();	
		f32 y = quat.getY();	
		f32 z = quat.getZ();

		float sqw = w*w;
		float sqx = x*x;
		float sqy = y*y;
		float sqz = z*z;

		euler.setZ((atan2(2.0f * (x*y + z*w),(sqx - sqy - sqz + sqw))));
		euler.setX((atan2(2.0f * (y*z + x*w),(-sqx - sqy + sqz + sqw))));
		euler.setY((asin(-2.0f * (x*z - y*w))));
	}

	//! Wandelt einen Euler-Rotationsvektor in einen Quaternion um
	void PhysicsBody::EulerXYZToQuaternion(btVector3 &euler, btQuaternion &quat) {	

		btMatrix3x3 mat;
		mat.setIdentity();
		mat.setEulerZYX(euler.getX(), euler.getY(), euler.getZ());
		mat.getRotation(quat);
	}

	//get mesh data. Bullet can use the meshbuffer data directly in btTriangleIndexVertexArray,
	// but Irrlicht indices are 16 bits wide which is not compatible with Bullet :(
	//So we are just using a btTriangleMesh instead, although it would probably
	// be faster to store the indices in int arrays and use these in a btTriangleIndexVertexArray
	btTriangleMesh* PhysicsBody::GetTriangleMesh(scene::IMesh* pMesh)
	{	
		btVector3 vertices[3];
		u32 i,j,k,index,numVertices;
		u16* mb_indices;

		btTriangleMesh *pTriMesh = new btTriangleMesh();
		for(i=0; i<pMesh->getMeshBufferCount(); i++) {

			irr::scene::IMeshBuffer* mb = pMesh->getMeshBuffer(i);

			//extract vertex data
			//because the vertices are stored as structs with no common base class,
			// we need to handle each type separately
			if (mb->getVertexType() == irr::video::EVT_STANDARD) {

				irr::video::S3DVertex* mb_vertices = (irr::video::S3DVertex*)mb->getVertices();
				mb_indices = mb->getIndices();
				numVertices = mb->getVertexCount();
				
				for (j=0; j<mb->getIndexCount();j+=3) { //get index into vertex list
					for (k=0; k<3; ++k) { //three verts per triangle
						index = mb_indices[j+k];
						if (index > numVertices) goto error;
						//convert to btVector3
						vertices[k] = btVector3(mb_vertices[index].Pos.X,mb_vertices[index].Pos.Y,mb_vertices[index].Pos.Z);		
					}
					pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
				}
			
			}
			else if (mb->getVertexType() == irr::video::EVT_2TCOORDS) {

				//same but for S3DVertex2TCoords data
				irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)mb->getVertices();
				u16* mb_indices = mb->getIndices();
				s32 numVertices = mb->getVertexCount();

				for(j=0; j<mb->getIndexCount(); j+=3){ //index into irrlicht data
					for (k=0; k<3; ++k) {
						s32 index = mb_indices[j+k];
						if (index > numVertices) goto error;
						vertices[k] = btVector3(mb_vertices[index].Pos.X,mb_vertices[index].Pos.Y,mb_vertices[index].Pos.Z);		
					}
					pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
				}
			}	
			//not bothering with EVT_TANGENTS vertex type
		}

		return pTriMesh;

	error:
		//should have better error handling than this
		delete pTriMesh;
		return 0;
	}

}}
