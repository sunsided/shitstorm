/** 
 * Project Vector
 * Mathematik-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _MATH_BINDINGS_H
#define _MATH_BINDINGS_H

#include "global.h"
#include "Scripting/Scripting.h"

namespace pv {
namespace scripting {

	//! Bindings für die Scripting-VM
	class MathBindings
	{
	public:

		//! Binding-Funktion
		static void scriptingBind(HSQUIRRELVM& vm);
	};

}}

#endif
