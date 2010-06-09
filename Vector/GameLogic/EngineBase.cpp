/** 
 * Project Vector
 * Engine Base
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "EngineBase.h"
#include <iostream>
#include "Scripting/Scripting.h"

using namespace std;
using namespace irr;

namespace pv {

	//! Erzeugt eine neue Instanz der EngineBase-Klasse.
	EngineBase::EngineBase(void) :
		irrlichtDevice(NULL), sceneManager(NULL), videoDriver(NULL), guiEnvironment(NULL), 
			engineClean(true), timer(NULL), paused(false), sceneStarted(false),
			sceneClearColor(irr::video::SColor(0, 64, 64, 64)),
			physicsManagement(NULL),
			worldManagement(NULL),
			audioManager(sound::SoundDeviceManager::get()),
			audioContext(NULL),
			audioDevice(NULL),
			audioListener(sound::RoamingSoundListener::get()),
			audioState(sound::SoundState::get()),
			vm(NULL),
			_isRunning(false)
	{
		initializeBasicMaterials();
	}

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
		irrlichtParams.Stencilbuffer = true; // stencilBuffer;
		irrlichtParams.Fullscreen = params.fullscreen;
		irrlichtParams.DriverType = driverType;
		irrlichtParams.Bits = params.bitsPerPixel;
		irrlichtParams.Doublebuffer = true;
		irrlichtParams.Vsync = false;
		irrlichtParams.ZBufferBits = params.zBitsPerPixel; // http://www.sjbaker.org/steve/omniv/love_your_z_buffer.html
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

		// Audiodevice erzeugen (erstbestes Device)
		audioDevice = audioManager->createAndInitDevice();
		if (!audioManager) return ESC_SOUND_DEVICE_FAILED;

		// Audiokontext erzeugen
		audioContext = audioDevice->createContext(true);
		if (!audioContext) return ESC_SOUND_CONTEXT_FAILED;

		// Physikmanagement erzeugen
		physicsManagement = new physics::PhysicsManager();
		if (!physicsManagement) return ESC_PHYSICS_FAILED;
		physicsManagement->initialize();
		
		// Weltmanagement erzeugen
		worldManagement = new world::WorldManager();
		if (!worldManagement) return ESC_WORLDMGMT_FAILED;

		// Scripting initialisieren
		try {
			vm = scripting::ScriptingVM::get();
			if (!vm) return ESC_SCRIPTVM_FAILED;

			// An die Scripting-VM binden
			bindToScriptingVM();

			// Abgeleitete Engine binden
			OnBindToScriptingVM();

			// Skript laden
			vm->executeScriptFile(L"scripts/scripting.nut"); // TODO: Hardcoding entsorgen!
		}
		catch(...) {
			return ESC_SCRIPTVM_FAILED;
		}

		// Standard-Audiostate setzen
		setDefaultAudioState();

		// Initialisieren
		cout << "Initialisiere Engine, 2nd stage ..." << endl;
		return OnSetupEngine();
	}

	//! Setzt den Audio-State auf Standardwerte
	void EngineBase::setDefaultAudioState() const {
		ASSERT(audioState);
		audioState->setDistanceModel(sound::SDM_EXPONENT_DISTANCE);
	}

	//! Schließt die Engine
	void EngineBase::close() {

		// Testen, ob wir bereits aufgeräumt haben
		if (engineClean) return;
		engineClean = true;

		cout << "Beende Engine ..." << endl;

		// OnClosing-Event in der VM triggern
		if (vm) vm->callEventIfExists("OnClosing");

		// Abgeleitete Klasse abschießen
		OnTeardownEngine();

		// Timer freigeben
		if (timer) {
			delete timer;
			timer = NULL;
		}

		// Device freigeben
		if (irrlichtDevice) {
			irrlichtDevice->drop();
			irrlichtDevice = NULL;
		}

		// Welt freigeben
		// Das Freigeben der Welt muss vor dem Freigeben der Physik geschehen
		if (worldManagement) {
			delete worldManagement;
			worldManagement = NULL;
		}

		// Physik freigeben
		// Das Freigeben der Physik muss nach dem Freigeben der Welt geschehen
		if (physicsManagement) {
			delete physicsManagement;
			physicsManagement = NULL;
		}
	}

	//! Startet die Haupt-Spielschleife
	EngineStatusCode EngineBase::run()
	{
		// Initialisierung überprüfen
		ASSERT(irrlichtDevice);
		cout << "Initialisiere Spielschleife ..." << endl;

		// Vorbereiten
		OnSetupScene();
		if (vm) vm->callEventIfExists("OnSetupScene");

		// Vorglühen
		irrlichtDevice->run();
		timer->update();

		// Ab dafür
		setRunning(true);

		// Spielschleife starten
		cout << "Starte Spielschleife ..." << endl;
		while(irrlichtDevice->run())
		{
			// Pausen handhaben
			if (shouldPause()) pause();
			else if(shouldUnpause()) unpause();
			
			// FPS setzen
			vm->setRootValue("FPS", (int)getFps());

			// Zeit ermitteln
			f32 deltaT = timer->update();

			// Preloop
			if (!OnPreSceneLoop(deltaT)) continue;

			// Szene durcharbeiten
			OnSceneLoop(deltaT);

			// Szene beenden, falls nötig
			endScene();
		}

		// Ab dafür
		setRunning(false);

		// Aufräumen
		cout << "Spielschleife beendet." << endl;
		close();

		return ESC_SUCCESS;
	}

	//! Hält das Spiel an
	void EngineBase::pause() {
		if (paused || !_isRunning) return;
		paused = true;

		// OnPause-Event in der VM triggern
		if (vm) vm->callEventIfExists("OnPause");

		//cout << "(Pause begonnen)" << endl;
		OnPause();
	}

	//! Setzt das Spiel fort
	void EngineBase::unpause() {
		if (!paused || !_isRunning) return;

		// OnUnpause-Event in der VM triggern
		if (vm) vm->callEventIfExists("OnUnpause");

		//cout << "(Pause beendet)" << endl;
		OnUnpause();
		paused = false;
	}

	//! Zeichnet einen Würfel zur Orientierung um die gewählte Kamera
	/**
	* @param camera Die aktive Kamera
	*/
	void EngineBase::drawCameraOrientationCage(scene::ICameraSceneNode *camera) {
		
		// Kameraposition ermitteln
		if (!camera) camera = sceneManager->getActiveCamera();
		core::vector3df cameraPosition = camera->getAbsolutePosition();
		f32 nearZ = camera->getNearValue();

		// Alte Transformation ermitteln und leere Transformation setzen
		core::matrix4 transformation = videoDriver->getTransform(video::ETS_WORLD);
		videoDriver->setTransform(video::ETS_WORLD, core::matrix4());

		// Material setzen und Käfig zeichnen
		videoDriver->setMaterial(getUnlitMaterial());
		videoDriver->draw3DBox(core::aabbox3df(-1.01f*nearZ+cameraPosition.X, -1.01f*nearZ+cameraPosition.Y, 1.1f*nearZ+cameraPosition.Z, 1.01f*nearZ+cameraPosition.X, 1.01f*nearZ+cameraPosition.Y, 1.1f*nearZ+cameraPosition.Z), video::SColor(255, 0, 0, 255));
		videoDriver->draw3DBox(core::aabbox3df(-1.01f*nearZ+cameraPosition.X, -1.01f*nearZ+cameraPosition.Y, -1.1f*nearZ+cameraPosition.Z, 1.01f*nearZ+cameraPosition.X, 1.01f*nearZ+cameraPosition.Y, -1.1f*nearZ+cameraPosition.Z), video::SColor(255, 0, 0, 192));
		videoDriver->draw3DBox(core::aabbox3df(1.1f*nearZ+cameraPosition.X, -1.01f*nearZ+cameraPosition.Y, -1.01f*nearZ+cameraPosition.Z, 1.1f*nearZ+cameraPosition.X, 1.01f*nearZ+cameraPosition.Y, 1.01f*nearZ+cameraPosition.Z), video::SColor(255, 255, 0, 0));
		videoDriver->draw3DBox(core::aabbox3df(-1.1f*nearZ+cameraPosition.X, -1.01f*nearZ+cameraPosition.Y, -1.01f*nearZ+cameraPosition.Z, -1.1f*nearZ+cameraPosition.X, 1.01f*nearZ+cameraPosition.Y, 1.01f*nearZ+cameraPosition.Z), video::SColor(255, 192, 0, 0));
		videoDriver->draw3DBox(core::aabbox3df(-1.01f*nearZ+cameraPosition.X, 1.1f*nearZ+cameraPosition.Y, -1.01f*nearZ+cameraPosition.Z, 1.01f*nearZ+cameraPosition.X, 1.1f*nearZ+cameraPosition.Y, 1.01f*nearZ+cameraPosition.Z), video::SColor(255, 0, 255, 0));
		videoDriver->draw3DBox(core::aabbox3df(-1.01f*nearZ+cameraPosition.X, -1.1f*nearZ+cameraPosition.Y, -1.01f*nearZ+cameraPosition.Z, 1.01f*nearZ+cameraPosition.X, -1.1f*nearZ+cameraPosition.Y, 1.01f*nearZ+cameraPosition.Z), video::SColor(255, 0, 192, 0));

		// Alte Transformation setzen
		videoDriver->setTransform(video::ETS_WORLD, transformation);
	}

	//! Initialisiert die Standardmaterialien
	void EngineBase::initializeBasicMaterials() {
		unlitMaterial.Lighting = false;
		unlitMaterial.Thickness = 1.0f;
	}

}