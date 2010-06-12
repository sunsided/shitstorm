/** 
 * Project Vector
 * Physik-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "PhysicsBindings.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/PhysicsObject.h"
#include "Physics/RigidBodyPhysicsObject.h"
#include "Physics/IrrBtConversion.h"

using namespace Sqrat;
using namespace irr;
using namespace irr::core;
using namespace pv::physics;

namespace pv {
namespace scripting {

	//! Wandelt den ActivationState in einen lesbaren String um
	SQChar* activationStateToString(PhysicsObject* object) {
		if (!object) return _SC("");
		switch (object->getActivationState()) {
		default: return _SC("(undefined)");
		case ACTIVE_TAG: return _SC("ACTIVE_TAG");
		case ISLAND_SLEEPING: return _SC("ISLAND_SLEEPING");
		case WANTS_DEACTIVATION: return _SC("WANTS_DEACTIVATION");
		case DISABLE_DEACTIVATION: return _SC("DISABLE_DEACTIVATION");
		case DISABLE_SIMULATION: return _SC("DISABLE_SIMULATION");
		}
	}

	//! Berechnet die lokale Trägheit
	irr::core::vector3df calculateLocalInertia(btCollisionShape* shape, irr::f32 mass) {
		btVector3 inertia;
		shape->calculateLocalInertia(mass, inertia);
		return conversion::toIrrlichtVector(inertia);
	}

	//! Holt die axis aligned bounding box eines Collision Shapes
	irr::core::aabbox3df getAabb(btCollisionShape* shape) {
		btTransform trafo;
		btVector3 _min, _max;
		shape->getAabb(trafo, _min, _max);
		
		irr::core::vector3df min = conversion::toIrrlichtVector(trafo * _min);
		irr::core::vector3df max = conversion::toIrrlichtVector(trafo * _max);
		
		return aabbox3df(min, max);
	}

	//! Erzeugt ein Box Shape
	btBoxShape* createBoxShape(const irr::core::vector3df& halfExtents) {
		btBoxShape *shape = new btBoxShape(conversion::toBulletVector(halfExtents));
		PhysicsManager::get()->registerCollisionShape(shape);
		return shape;
	}

	//! Ermittelt die ID des Shapes
	irr::u32 getShapeId(btCollisionShape *shape) {
		utility::Manager<btCollisionShape> manager = PhysicsManager::get()->getCollisionShapeManager();
		return manager.getId(shape);
	}

	//! Bindet die Klasse
	void PhysicsBindings::scriptingBind(HSQUIRRELVM& vm) {

		// Bullet-Kram
		RootTable(vm).Bind( _SC("BtTransform"),
			Class<btTransform, NoConstructor>(vm)
			);

		// Bullet-Kram
		RootTable(vm).Bind( _SC("BtCollisionShape"),
			Class<btCollisionShape, NoConstructor>(vm)
				.Prop(_SC("IsCompound"), &btCollisionShape::isCompound)
				.Prop(_SC("IsConvex"), &btCollisionShape::isConvex)
				.Prop(_SC("IsConvex2d"), &btCollisionShape::isConvex2d)
				.Prop(_SC("IsNonMoving"), &btCollisionShape::isNonMoving)
				.Prop(_SC("IsSoftBody"), &btCollisionShape::isSoftBody)
				.Func(_SC("getAngularMotionDisc"), &btCollisionShape::getAngularMotionDisc)
				.Func(_SC("getContactBreakingThreshold"), &btCollisionShape::getContactBreakingThreshold)
				.Prop(_SC("ShapeType"), &btCollisionShape::getShapeType)
				.GlobalFunc(_SC("calculateLocalInertia"), &calculateLocalInertia)
				.GlobalFunc(_SC("getAabb"), &getAabb)
				.GlobalFunc(_SC("getId"), &getShapeId)
			);

		// Bullet-Kram
		RootTable(vm).Bind( _SC("BtBoxShape"),
			DerivedClass<btBoxShape, btCollisionShape, NoConstructor>(vm)
				.StaticFunc(_SC("create"), &createBoxShape)
			);

		// Physikobjekt
		RootTable(vm).Bind( _SC("PhysicsObject"), 
			Class<PhysicsObject, NoConstructor>(vm)
				.Prop(_SC("Mass"), &PhysicsObject::getMass)
				.Prop(_SC("Position"), &PhysicsObject::getPosition, &PhysicsObject::setPosition)
				.Prop(_SC("Rotation"), &PhysicsObject::getRotation, &PhysicsObject::setRotation)
				.Prop(_SC("LinearVelocity"), &PhysicsObject::getLinearVelocity, &PhysicsObject::setLinearVelocity)
				.Prop(_SC("AngularVelocity"), &PhysicsObject::getAngularVelocity, &PhysicsObject::setAngularVelocity)
				.Func(_SC("applyForce"), &PhysicsObject::applyForce)
				.Func(_SC("zeroForces"), &PhysicsObject::zeroForces)
				.Prop(_SC("ActivationState"), &PhysicsObject::getActivationState, &PhysicsObject::setActivationStateC)
				.Prop(_SC("SimulationEnabled"), &PhysicsObject::getSimulationEnabled, &PhysicsObject::setSimulationEnabled)
				.Func<void(PhysicsObject::*)(f32)>(_SC("updateMass"), &PhysicsObject::updateMass)
				.Func<void(PhysicsObject::*)(f32,const vector3df&)>(_SC("updateMassAndInertia"), &PhysicsObject::updateMass)
				.Prop(_SC("IsRigidBody"), &PhysicsObject::isRigidBody)
				.Prop(_SC("getWorld"), &PhysicsObject::getPhysicsWorld)
				.GlobalFunc(_SC("getActivationStateString"), &activationStateToString)
				.Func(_SC("poke"), &PhysicsObject::makeActive)
				.Func(_SC("setActivationState"), &PhysicsObject::setActivationState)
				.Func(_SC("getActivationState"), &PhysicsObject::getActivationState)
				.Func(_SC("setDeactivationTime"), &PhysicsObject::setDeactivationTime)
				.Func(_SC("getDeactivationTime"), &PhysicsObject::getDeactivationTime)
				.Func(_SC("forceActivationState"), &PhysicsObject::forceActivationState)
				.Prop(_SC("IsStatic"), &PhysicsObject::isStatic)
				.Func(_SC("CollisionShape"), &PhysicsObject::getCollisionShape)
			);

		// Physikobjekt
		RootTable(vm).Bind( _SC("PhysicsObject"), 
			DerivedClass<RigidBodyPhysicsObject, PhysicsObject, NoConstructor>(vm)
			);

		// Welt
		RootTable(vm).Bind( _SC("PhysicsWorld"), 
			Class<PhysicsWorld, NoConstructor>(vm)
				.Func(_SC("isInitialized"), &PhysicsWorld::isInitialized)
				.Func(_SC("getGravity"), &PhysicsWorld::getGravityAsIrrVector)
				.Func(_SC("getManager"), &PhysicsWorld::getManager)
				.Func(_SC("getObject"), &PhysicsWorld::getObject)
				.Prop(_SC("ObjectCount"), &PhysicsWorld::getObjectCount)
			);

		// Manager
		RootTable(vm).Bind(
			_SC("PhysicsManager"),
			Class<PhysicsManager, NoConstructor>(vm)
				.Func(_SC("getWorld"), &PhysicsManager::getPhysicsWorld)
				.Func(_SC("createWorld"), &PhysicsManager::createPhysicsWorld)
				.Prop(_SC("WorldCount"), &PhysicsManager::getWorldCount)
				.Func(_SC("getCollisionShape"), &PhysicsManager::getCollisionShape)
			);
	}

}}
