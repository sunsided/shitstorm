/** 
 * Project Vector
 * World-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _WORLD_BINDINGS_H
#define _WORLD_BINDINGS_H

#include "global.h"
#include "Scripting/Scripting.h"

namespace pv {
namespace scripting {

	//! Manager für beliebige Typen.
	class WorldBindings
	{
	public:

		//! Binding-Funktion
		static void scriptingBind(HSQUIRRELVM& vm);
	};

}}

#endif
