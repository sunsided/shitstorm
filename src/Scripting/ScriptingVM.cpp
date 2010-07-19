/** 
 * Project Vector
 * Scripting-VM
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "ScriptingVM.h"
#include "Bindings.h"

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

using namespace Sqrat;

#ifndef VSPRINTF_BUFFER_SIZE
#define VSPRINTF_BUFFER_SIZE 2048
#endif

namespace pv {
namespace scripting {

	//! Print-Funktion f�r Squirrel
	static void squirrelPrintFunc(HSQUIRRELVM v, const SQChar * s,...) {
		static SQChar temp[VSPRINTF_BUFFER_SIZE];
		va_list vl;
		va_start(vl, s);
		scvsprintf(temp, VSPRINTF_BUFFER_SIZE, s, vl); // TODO: Dynamische Puffer!?
		std::wcout << temp << std::endl;
		va_end(vl);
	}

	//! Print-Funktion f�r Squirrel
	static void squirrelPrintErrorFunc(HSQUIRRELVM v, const SQChar * s,...) {
		static SQChar temp[VSPRINTF_BUFFER_SIZE];
		va_list vl;
		va_start(vl, s);
		scvsprintf(temp, VSPRINTF_BUFFER_SIZE, s, vl); // TODO: Dynamische Puffer!?
		std::wcerr << temp << std::endl;
		va_end(vl);
	}

	//! srand-Funktion f�r Squirrel, die das Original ersetzt
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
		sq_setprintfunc(vm, squirrelPrintFunc, squirrelPrintErrorFunc);

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
		//ConstTable(vm).Const(L"SQUIRREL_VERSION", SQUIRREL_VERSION);

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
		executeScriptCode(L"print(\"Scripting VM initialisiert: \" + _version_);");

		// Klassen binden
		bindElements(vm);
		executeScriptCode(L"print(\"Scripting VM: Elemente gebunden.\");");
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

	//! F�hrt ein Script (inline) aus
	void ScriptingVM::executeScriptCode(const irr::core::stringw nuttingham) const {
		Sqrat::Script script;
		try {
			script.CompileString(nuttingham.c_str());
			script.Run();
		}
		catch(Sqrat::Exception e) {
			std::wcerr << "Fehler beim Ausf�hren eines Skriptes: " << e.Message() << std::endl;
		}
		catch(...) {
			std::wcerr << "Fehler beim Ausf�hren des Skriptes." << std::endl;
		}
	}

	//! F�hrt ein Script (Datei) aus
	/* @code vm->executeScriptFile(L"/path/to/file/script.nut"); @endcode
		*/
	void ScriptingVM::executeScriptFile(const irr::core::stringw filename) const {
		Sqrat::Script script;
		try {
			script.CompileFile(filename.c_str());
			script.Run();
		}
		catch(Sqrat::Exception e) {
			std::wcerr << "Fehler beim Ausf�hren des Skriptes '" << filename.c_str() << "': " << e.Message() << std::endl;
		}
		catch(...) {
			std::wcerr << "Fehler beim Ausf�hren des Skriptes '" << filename.c_str() << "'." << std::endl;
		}
	}

	//! Bindet die Klassen
	void ScriptingVM::bindElements(HSQUIRRELVM& vm) {
		pv::scripting::bindElements(vm);
	}

	//! Ruft ein Event auf, falls es existiert
	/* @returns true, wenn das Event aufgerufen wurde, ansonsten false. */
	bool ScriptingVM::callEventIfExists(const irr::core::stringw eventName) const {

		HSQUIRRELVM vm = DefaultVM::Get();

		Function function(RootTable(vm), eventName.c_str());
		if (function.IsNull()) return false;
		try {
			function.Execute();
		}
		catch(Exception e) {
			std::wcerr << "Fehler beim Ausführen des Events '" << eventName.c_str() << "': " << e.Message() << std::endl;
		}
		catch(...) {
			std::wcerr << "Fehler beim Ausführen des Events '" << eventName.c_str() << "'." << std::endl;
		}
		return true;
	}

	//! Setzt eine Konstante
	void ScriptingVM::setRootValue(irr::core::stringw name, int value) {
		RootTable().SetValue(name.c_str(), value);
	}

	//! Setzt eine Konstante
	void ScriptingVM::setRootValue(irr::core::stringw name, float value) {
		RootTable().SetValue(name.c_str(), value);
	}

	//! Setzt eine Konstante
	void ScriptingVM::setRootValue(irr::core::stringw name, irr::core::stringw value) {
		RootTable().SetValue(name.c_str(), value.c_str());
	}

}}
