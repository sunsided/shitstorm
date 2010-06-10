/** 
 * Project Vector
 * Scene-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SCENE_BINDINGS_H
#define _SCENE_BINDINGS_H

#include "global.h"
#include "Scripting/Scripting.h"

namespace pv {
namespace scripting {

	//! Manager für beliebige Typen.
	class SceneBindings
	{
	public:

		//! Binding-Funktion
		static void scriptingBind(HSQUIRRELVM& vm);
	};

}}

#endif
