/** 
 * Project Vector
 * Physik-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICS_BINDINGS_H
#define _PHYSICS_BINDINGS_H

#include "global.h"
#include "Scripting/Scripting.h"

namespace pv {
namespace scripting {

	//! Bindings für die Scripting-VM
	class PhysicsBindings
	{
	public:

		//! Binding-Funktion
		static void scriptingBind(HSQUIRRELVM& vm);
	};

}}

#endif
