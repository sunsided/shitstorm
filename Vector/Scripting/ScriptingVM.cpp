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
#include <time.h>
#include <limits.h>

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

	static SQInteger math_srand(HSQUIRRELVM v)
	{
		SQInteger i;
		if(SQ_FAILED(sq_getinteger(v,2,&i)))
			return sq_throwerror(v,_SC("invalid param"));
		srand((unsigned int)i);
		return 0;
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
		
		// Zufallszahlengenerator
		srand((unsigned int)(time(NULL) % UINT_MAX));

		// VM initialisieren
		SquirrelVM::Init();

		// Print-Funktion setzen
		initialized = true;

		// Testskript ausgeben
		irr::core::stringw script = L"print(\"Scripting VM initialisiert: ";
		script += SQUIRREL_VERSION;
		script += L"\");";
		executeScriptCode(script);
	}

	//! Terminiert die VM
	void ScriptingVM::terminate() {
		if (!initialized) return;

		// Testskript ausgeben
		executeScriptCode(_T("print(\"Squirrel VM wird heruntergefahren.\");"));

		// Beenden
		SquirrelVM::Shutdown();
		initialized = false;
	}

	//! Führt ein Script (inline) aus
	void ScriptingVM::executeScriptCode(const irr::core::stringw nuttingham) const {
		SquirrelObject script = SquirrelVM::CompileBuffer(nuttingham.c_str());
		SquirrelVM::RunScript(script);
	}

}}