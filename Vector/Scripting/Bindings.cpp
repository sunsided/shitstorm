/** 
 * Project Vector
 * Helfer für Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _IMPLEMENT_BINDINGS
#include "Bindings.h"
#include "BindingList.h"

namespace pv {
namespace scripting {

	//! Bindet die Klassen an das Scripting-System
	void bindElements(HSQUIRRELVM& vm) {

		// Vektor binden
		BridgeVector3::scriptingBind(vm);
	}

}}
