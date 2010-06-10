/** 
 * Project Vector
 * Irrlicht-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "SceneBindings.h"
#include "SceneNodes/SceneObject.h"

using namespace Sqrat;
using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace pv::nodes;

namespace pv {
namespace scripting {

	//! Bindet die Klasse
	void SceneBindings::scriptingBind(HSQUIRRELVM& vm) {

		RootTable(vm).Bind(
			_SC("SceneObject"),
			Class<SceneObject, NoConstructor>(vm)
				.Prop(_SC("Visible"), &SceneObject::getVisibility, &SceneObject::setVisibility)
				.Prop(_SC("TrulyVisible"), &SceneObject::isTrulyVisible)
			);
	}

}}
