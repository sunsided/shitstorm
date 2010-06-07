/**
 * Project Shitstorm: Vector (Vectorstorm? Shitvector?)
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


//#include "global.h"
#include "linker.h"

//#include "GameLogic/GameEngine.h"
//#include "Scripting/ScriptingVM.h"
#include <sqplus.h>

/*
#include <memory>
#include <iostream>

using namespace std;
*/
//using namespace pv;

int main(int argc, char **argv) {

	/*
	scripting::ScriptingVM *vm = new scripting::ScriptingVM();
	vm->initialize();
	vm->terminate();
	delete vm;
	*/
	/*
	// Engine erzeugen
	auto_ptr<EngineBase> engine( new GameEngine() );
	if (!engine.get()) {
		cerr << "Engine konnte nicht erzeugt werden." << endl;
		return ESC_INSTANCIATION_FAILED;
	}

	// Initialisierungsparameter erzeugen
	EngineInitializationParams params;

	// Engine initialisieren
	EngineStatusCode result = engine->initialize(params);
	if (result != ESC_SUCCESS) {
		cerr << "Engine konnte nicht initialisiert werden. Fehlercode: " << result << endl;
		return result;
	}

	// Engine starten
	result = engine->run();

	// Engine freigeben und Spiel beenden
	return result;
	*/
	return 1;
}