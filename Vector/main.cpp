/**
 * Project Shitstorm: Vector (Vectorstorm? Shitvector?)
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "global.h"
#include "linker.h"

#include "GameLogic/GameEngine.h"
#include "Sound/SoundDeviceManager.h"
#include "Sound/OggVorbisAudioSource.h"

#include <memory>
#include <iostream>

using namespace std;
using namespace pv;

int main(int argc, char **argv) {

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
}