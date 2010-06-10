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

	//! Bindet die Klasse
	void PhysicsBindings::scriptingBind(HSQUIRRELVM& vm) {

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
			);
	}

}}
