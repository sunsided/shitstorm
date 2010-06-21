/** 
 * Project Vector
 * Irrlicht-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _IRRLICHT_BINDINGS_H
#define _IRRLICHT_BINDINGS_H

#include "global.h"
#include "Scripting/Scripting.h"

namespace pv {
namespace scripting {

	//! Bindings für die Scripting-VM
	class IrrlichtBindings
	{
	public:

		//! Binding-Funktion
		static void scriptingBind(HSQUIRRELVM& vm);

		//! Binding-Funktion für Enumerationswerte
		static void scriptingBindEnums(HSQUIRRELVM& vm);
	};

}}

#endif
