/** 
 * Project Vector
 * Scripting-VM
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "ScriptingVM.h"

// SQUIRREL!
#include <sqstdio.h> 
#include <sqstdaux.h> 

namespace pv {
namespace scripting {

	//! Erzeugt eine neue Instanz der VM
	ScriptingVM::ScriptingVM() 
		: vm(NULL)
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

		// VM erzeugen
		vm = new HSQUIRRELVM();
		*vm = sq_open(1024); // creates a VM with initial stack size 1024 
	}

	//! Terminiert die VM
	void ScriptingVM::terminate() {
		if (vm) {
			sq_close(*vm); 
			delete vm;
			vm = NULL;
		}
	}

}}