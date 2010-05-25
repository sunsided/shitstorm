/** 
 * Project Vector
 * Engine Base
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "EngineBase.h"

#include <iostream>

using namespace std;
using namespace irr;

namespace pv {

	//! Destruktor.
	EngineBase::~EngineBase(void)
	{
		close();
	}

	//! Ermittelt den Videotreiber
	/**
	* @param driverHint	Der vom Benutzer gewählte Treiber
	* @returns				Der von der Irrlicht-Engine zu verwendende Treiber
	*/
	video::E_DRIVER_TYPE EngineBase::selectVideoDriver(VideoDriver driverHint) const
	{
		video::E_DRIVER_TYPE driverType = video::EDT_NULL;

		switch (driverHint) {
			case VD_SOFTWARE:
				driverType = video::EDT_BURNINGSVIDEO;
				break;
			case VD_DIRECTX:
				// TODO: Automatisch zwischen D3D9 und D3D8 wählen
				driverType = video::EDT_DIRECT3D9;
				break;
			case VD_OPENGL:
				driverType = video::EDT_OPENGL;
				break;
		}

		ASSERT(driverType != video::EDT_NULL);
		return driverType;
	}

	//! Initialisiert die Engine
	EngineStatusCode EngineBase::initialize(EngineInitializationParams &params) {

		// Engine als "dirty" markieren
		cout << "Initialisiere Engine, 1st stage ..." << endl;
		engineClean = false;

		// Videotreiber ermitteln
		video::E_DRIVER_TYPE driverType = selectVideoDriver(params.driver);

		// Irrlicht parameterieren
		SIrrlichtCreationParameters irrlichtParams;
		irrlichtParams.AntiAlias = 0; // EAAM_QUALITY;
		irrlichtParams.WindowSize = params.screenSize;
		irrlichtParams.Stencilbuffer = false; // stencilBuffer;
		irrlichtParams.Fullscreen = params.fullscreen;
		irrlichtParams.DriverType = driverType;
		irrlichtParams.Bits = params.bitsPerPixel;
		irrlichtParams.Doublebuffer = true;
		irrlichtParams.Vsync = false;
		irrlichtParams.ZBufferBits = params.bitsPerPixel;
		irrlichtParams.EventReceiver = 0;// &eventReceiver;

		// Device erzeugen
		irrlichtDevice = irr::createDeviceEx( irrlichtParams );
		if (!irrlichtDevice) return ESC_DEVICE_CREATION_FAILED;

		// Videotreiber beziehen
		videoDriver = irrlichtDevice->getVideoDriver();
		if (!videoDriver) return ESC_VIDEO_DRIVER_FAILED;

		// Szenenmanager beziehen
		sceneManager = irrlichtDevice->getSceneManager();
		if (!sceneManager) return ESC_SMGR_FAILED;

		// GUI beziehen
		guiEnvironment = irrlichtDevice->getGUIEnvironment();
		if (!guiEnvironment) return ESC_GUIENV_FAILED;

		// Fenstertitel setzen
		irrlichtDevice->setWindowCaption(params.windowTitle);

		// Timer erzeugen
		timer = new GameTimer(irrlichtDevice);
		ASSERT(timer);

		// Initialisieren
		cout << "Initialisiere Engine, 2nd stage ..." << endl;
		return OnSetupEngine();
	}

	//! Schließt die Engine
	void EngineBase::close() {

		// Testen, ob wir bereits aufgeräumt haben
		if (engineClean) return;
		engineClean = true;

		cout << "Beende Engine ..." << endl;

		// Abgeleitete Klasse abschießen
		OnTeardownEngine();

		// Device freigeben
		if(irrlichtDevice) {
			irrlichtDevice->closeDevice();
			irrlichtDevice = NULL;
		}

		// Timer freigeben
		if (timer) {
			delete timer;
			timer = NULL;
		}
	}

	//! Startet die Haupt-Spielschleife
	EngineStatusCode EngineBase::run()
	{
		// Initialisierung überprüfen
		// TODO: Exception werfen
		ASSERT(irrlichtDevice);
		cout << "Starte Spielschleife ..." << endl;

		// Motor vorglühen
		irrlichtDevice->run();
		timer->update();

		// Spielschleife starten
		while(irrlichtDevice->run())
		{
			// Pausen handhaben
			if (shouldPause()) pause();
			else if(shouldUnpause()) unpause();

			// Zeit ermitteln
			f32 deltaT = timer->update();

			// Preloop
			if (!OnPreSceneLoop(deltaT)) continue;

			// Szene durcharbeiten
			OnSceneLoop(deltaT);

			// Szene beenden, falls nötig
			endScene();
		}

		// Aufräumen
		cout << "Spielschleife beendet." << endl;
		close();

		return ESC_SUCCESS;
	}

	//! Hält das Spiel an
	void EngineBase::pause() {
		if (paused) return;
		paused = true;

		cout << "(Pause begonnen)" << endl;
		OnPause();
	}

	//! Setzt das Spiel fort
	void EngineBase::unpause() {
		if (!paused) return;

		cout << "(Pause beendet)" << endl;
		OnUnpause();
		paused = false;
	}

}