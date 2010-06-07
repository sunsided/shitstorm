/** 
 * Project Vector
 * Scripting-VM
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "ScriptingVM.h"

// Squirrel!
#include <sqplus.h>

namespace pv {
namespace scripting {

	//! Erzeugt eine neue Instanz der VM
	ScriptingVM::ScriptingVM()
	{
	}

	//! Destruktor
	ScriptingVM::~ScriptingVM() 
	{
		terminate();
	}

	//! Initialisiert die VM.
	/** Muss als erste Funktion aufgerufen werden.
	*/
	void ScriptingVM::initialize(irr::u32 stackSize) {
		terminate();

	}

	//! Terminiert die VM
	void ScriptingVM::terminate() {
		
	}

}}