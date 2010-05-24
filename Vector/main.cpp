/**
 * Project Shitstorm: Vector (Vectorstorm? Shitvector?)
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "global.h"
#include "linker.h"

#include "GameLogic\EngineBase.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	// Engine erzeugen
	pv::EngineBase *engine = NULL;
	if (!engine) {
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
	return engine->run();
}