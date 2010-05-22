#include "Engine.h"

Engine::~Engine(void)
{
	if(device) device->drop();
}

int Engine::createDevice(int width, int height, bool fullscreen, bool stencilBuffer)
{
	// Bildschirmgröße setzen
	screenSize = dimension2d<u32>(width, height);

	// ask user for driver
	video::E_DRIVER_TYPE driverType= EDT_DIRECT3D9;

	// Parameter
	SIrrlichtCreationParameters params;
	params.AntiAlias = 0;
	params.WindowSize = screenSize;
	params.Stencilbuffer = stencilBuffer;
	params.Fullscreen = fullscreen;
	params.DriverType = driverType;
	params.Bits = 16;
	params.Doublebuffer = true;
	params.Vsync = false;
	params.ZBufferBits = 16;
	params.EventReceiver = &eventReceiver;
	
	// EventReceiver initialisieren
	eventReceiver.init();

	// Rendering-Device erstellen
	//device = irr::createDevice( driverType, screenSize, 16, fullscreen, stencilBuffer, false, 0);
	device = irr::createDeviceEx( params );
	if (!device) return -2;

	// Timer beziehen
	timer = new GameTimer(device);

	// Videotreiber beziehen
	driver = device->getVideoDriver();
	if (!driver) return -3;

	// Szenenmanager beziehen
	smgr = device->getSceneManager();
	if (!smgr) return -4;

	// GUI beziehen
	guienv = device->getGUIEnvironment();
	if (!guienv) return -5;

	// Setup starten
	return setup();
}

int Engine::setup(void)
{
	return SUCCESS;
}

int Engine::teardown(void)
{
	return SUCCESS;
}

void Engine::setWindowTitle(const wchar_t *title)
{
	if (!device) return;
	this->windowTitle = title;
	device->setWindowCaption(title);
}

int Engine::run(void)
{
	if (!device) return -1;

	// Device vorglühen
	device->run();

	// Timer vorglühen
	timer->update();

	// Spielschleife starten
	while(device->run())
    {
		// Timer aktualisieren und Zeit seit dem letzten Frame ermitteln
		timer->update();
		u32 deltaT = timer->getLastFrameTime();

		// Titel anzeigen
		core::stringw tmp(this->windowTitle);
		tmp += L" [";
		tmp += driver->getName();
		tmp += L"; fps: ";
		tmp += getFps();
		tmp += L" ]";
		device->setWindowCaption(tmp.c_str());

		// Events beenden
		eventReceiver.endEventProcess();

		// Szene durcharbeiten
		sceneLoop(deltaT);

		// Events starten
		eventReceiver.startEventProcess();
    }

	// Aufräumen
	teardown();

	return SUCCESS;
}

u32 Engine::getFps() 
{
	if (!driver) return 0;
	return driver->getFPS();
}