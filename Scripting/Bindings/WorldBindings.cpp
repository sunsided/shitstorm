/** 
 * Project Vector
 * Irrlicht-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "WorldBindings.h"
#include "World/WorldManager.h"
#include "World/WorldObject.h"
#include "World/ObjectClass.h"
#include "World/ObjectClassGroup.h"

using namespace Sqrat;
using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace pv::world;

namespace pv {
namespace scripting {

	//! Bindet die Klasse
	void WorldBindings::scriptingBind(HSQUIRRELVM& vm) {

		RootTable(vm).Bind(
			_SC("ObjectClass"),
			Class<ObjectClass, NoConstructor>(vm)
				.Prop(_SC("Id"), &ObjectClass::getId)
				.Prop(_SC("Desc"), &ObjectClass::getDescription, &ObjectClass::setDescription)
			);
		
		RootTable(vm).Bind(
			_SC("WorldObject"),
			Class<WorldObject, NoConstructor>(vm)
				.Prop(_SC("ID"), &WorldObject::getWorldObjectId)
				.Prop(_SC("PhysicsEnabled"), &WorldObject::physicsEnabled, &WorldObject::enablePhysics)
				.Prop(_SC("Visible"), &WorldObject::getVisibility, &WorldObject::setVisibility)
				.Func(_SC("hideAndDisable"), &WorldObject::hideAndDisable)
				.Prop(_SC("Physics"), &WorldObject::getPhysicsBody)
				.Prop(_SC("Scene"), &WorldObject::getSceneObject)
			);

		RootTable(vm).Bind(
			_SC("WorldManager"),
			Class<WorldManager, NoConstructor>(vm)
				.Func(_SC("getObjectCount"), &WorldManager::worldObjectCount)
				.Func(_SC("clearAllObjects"), &WorldManager::clearAllObjects)
				.Func<void(WorldManager::*)(irr::u32)>(_SC("removeObjects"), &WorldManager::removeWorldObject)
				.Func(_SC("getObject"), &WorldManager::getWorldObject)
			);
	}

}}
