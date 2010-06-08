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

#include <sqstdstring.h>
#include <sqstdaux.h>
#include <sqstdmath.h>
#include <sqstdio.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>

namespace pv {
namespace scripting {

	//! Print-Funktion für Squirrel
	static void squirrelPrintFunc(HSQUIRRELVM v, const SQChar * s,...) {
		static SQChar temp[2048];
		va_list vl;
		va_start(vl, s);
		scvsprintf(temp, s, vl); // TODO: Dynamische Puffer!?
		std::wcout << temp << std::endl;
		va_end(vl);
	}

	//! srand-Funktion für Squirrel, die das Original ersetzt
	static void squirrelSrandFunc(irr::u32 i)
	{
		srand((unsigned int)i);
	}

	//! Erzeugt eine neue Instanz der VM
	ScriptingVM::ScriptingVM()
		: initialized(false)
	{
		memset(&vm, 0, sizeof(HSQUIRRELVM));
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
		
		using namespace Sqrat;

		// Zufallszahlengenerator
		srand((unsigned int)(time(NULL) % UINT_MAX));

		// VM initialisieren
		vm = sq_open(stackSize);
		sqstd_seterrorhandlers(vm);
		sq_setprintfunc(vm, squirrelPrintFunc);

		// Standardbibliotheken laden
		sq_pushroottable(vm);
		sqstd_register_stringlib(vm);
		sqstd_register_systemlib(vm);
		sqstd_register_mathlib(vm);
		sqstd_register_bloblib(vm);
		sqstd_register_iolib(vm);

		// Default-VM setzen
		DefaultVM::Set(vm);

		// Funktionen ersetzen
		RootTable(vm).Func(L"srand", &squirrelSrandFunc);

		// Testaufruf
		/*
		{
			int top = sq_gettop(vm);
			sq_pushroottable(vm);
			SQRESULT result = sqstd_dofile(vm, L"scripts\\scripting.nut", 0, 1);
			sq_settop(vm, top);
		}
		*/

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
		executeScriptCode(L"print(\"Squirrel VM wird heruntergefahren.\");");

		// Beenden
		sq_close(vm);
		initialized = false;
	}

	//! Führt ein Script (inline) aus
	void ScriptingVM::executeScriptCode(const irr::core::stringw nuttingham) const {
		Sqrat::Script script;
		script.CompileString(nuttingham.c_str());
		script.Run();
	}

	//! Führt ein Script (Datei) aus
	/* @code vm->executeScriptFile(L"/path/to/file/script.nut"); @endcode
		*/
	void ScriptingVM::executeScriptFile(const irr::core::stringw filename) const {
		Sqrat::Script script;
		script.CompileFile(filename.c_str());
		script.Run();
	}

}}