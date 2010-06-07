/** 
 * Project Vector
 * Scripting-VM
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "ScriptingVM.h"

#include <stdio.h>
#include <stdarg.h>
#include <iostream>

// Squirrel!
#include <sqplus.h>

namespace pv {
namespace scripting {

	//! Print-Funktion für Squirrel
	static void squirrelPrintFunc(HSQUIRRELVM v, const SQChar * s,...) {
		static SQChar temp[2048];
		va_list vl;
		va_start(vl, s);
		scvsprintf(temp, s, vl); // TODO: Dynamische Puffer!?
		SCPUTS(temp);
		va_end(vl);
	}

	//! Erzeugt eine neue Instanz der VM
	ScriptingVM::ScriptingVM()
		: initialized(false)
	{
		initialize();
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
		
		// VM initialisieren
		SquirrelVM::Init();

		// Print-Funktion setzen
		sq_setprintfunc(SquirrelVM::GetVMPtr(), squirrelPrintFunc);
		initialized = true;

		// Testskript ausgeben
		SquirrelObject script = SquirrelVM::CompileBuffer(_T("print(\"Squirrel VM initialisiert.\");"));
		SquirrelVM::RunScript(script);
	}

	//! Terminiert die VM
	void ScriptingVM::terminate() {
		if (!initialized) return;

		// Testskript ausgeben
		SquirrelObject script = SquirrelVM::CompileBuffer(_T("print(\"Squirrel VM wird heruntergefahren.\");"));
		SquirrelVM::RunScript(script);

		// Beenden
		SquirrelVM::Shutdown();
		initialized = false;
	}

}}