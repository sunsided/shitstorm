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
			_SC("WorldManager"),
			Class<WorldManager, NoConstructor>(vm)
				.Func(_SC("getObjectCount"), &WorldManager::worldObjectCount)
				.Func(_SC("clearAllObjects"), &WorldManager::clearAllObjects)
				.Func<void(WorldManager::*)(irr::u32)>(_SC("removeObjects"), &WorldManager::removeWorldObject)
			);
	}

}}
