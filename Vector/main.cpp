/**
 * Project Shitstorm: Vector (Vectorstorm? Shitvector?)
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "global.h"
#include "linker.h"

#include "GameLogic\GameEngine.h"

#include <memory>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	// Engine erzeugen
	auto_ptr<pv::EngineBase> engine( new pv::GameEngine() );
	if (!engine.get()) {
		cerr << "Engine konnte nicht erzeugt werden." << endl;
		return pv::ESC_INSTANCIATION_FAILED;
	}

	// Initialisierungsparameter erzeugen
	pv::EngineInitializationParams params;

	// Engine initialisieren
	pv::EngineStatusCode result = engine->initialize(params);
	if (result != pv::ESC_SUCCESS) {
		cerr << "Engine konnte nicht initialisiert werden. Fehlercode: " << result << endl;
		return result;
	}

	// Engine starten
	result = engine->run();

	// Engine freigeben und Spiel beenden
	return result;
}