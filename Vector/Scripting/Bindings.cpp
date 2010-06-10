/** 
 * Project Vector
 * Helfer für Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _IMPLEMENT_BINDINGS
#include "Bindings.h"

#include "Bindings/MathBindings.h"
#include "Bindings/BridgeVector3.h"
#include "Bindings/IrrlichtBindings.h"
#include "Bindings/WorldBindings.h"
#include "Bindings/PhysicsBindings.h"

namespace pv {
namespace scripting {

	//! Bindet die Klassen an das Scripting-System
	void bindElements(HSQUIRRELVM& vm) {

		// Vektor binden
		BridgeVector3::scriptingBind(vm);

		// Irrlicht-Bindings
		IrrlichtBindings::scriptingBind(vm);

		// Mathematikkram
		MathBindings::scriptingBind(vm);

		// Physikkram
		PhysicsBindings::scriptingBind(vm);

		// Weltkram
		WorldBindings::scriptingBind(vm);
	}

}}
