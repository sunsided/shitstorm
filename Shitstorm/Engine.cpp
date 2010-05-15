#include "Engine.h"
#include <driverChoice.h>

Engine::Engine(void) 
{
}

Engine::~Engine(void)
{
	if(device) device->drop();
}

int Engine::createDevice(int width, int height, bool fullscreen, bool stencilBuffer)
{
	// Bildschirmgröße setzen
	screenSize = dimension2d<u32>(width, height);

	// ask user for driver
	video::E_DRIVER_TYPE driverType= E_DRIVER_TYPE::EDT_DIRECT3D9;

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
	params.EventReceiver = 0;

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

	return setup();
}

int Engine::setup(void)
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

		// Szene durcharbeiten
		sceneLoop(deltaT);
    }

	return SUCCESS;
}

u32 Engine::getFps() 
{
	if (!driver) return 0;
	return driver->getFPS();
}