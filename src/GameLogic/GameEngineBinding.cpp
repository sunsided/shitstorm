/** 
 * Project Vector
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "GameEngine.h"
#include "Scripting/Scripting.h"

namespace pv {

	//! Bindet die Engine an die Scripting-VM
	/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
	void GameEngine::OnBindToScriptingVM() {
		using namespace Sqrat;
		using namespace scripting;
		using namespace irr::core;

		// VM holen
		HSQUIRRELVM vm = DefaultVM::Get();
	}

}
