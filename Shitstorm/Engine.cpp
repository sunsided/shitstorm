#include "Engine.h"

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
	if(device) device->drop();
}

int Engine::createDevice(void)
{
	// Rendering-Device erstellen
	device = irr::createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, 0);
	if (!device) return -1;

	// Videotreiber beziehen
	driver = device->getVideoDriver();
	if (!driver) return -2;

	// Szenenmanager beziehen
	smgr = device->getSceneManager();
	if (!smgr) return -3;

	// GUI beziehen
	guienv = device->getGUIEnvironment();
	if (!guienv) return -4;

	return setup();
}

int Engine::setup(void)
{
	return SUCCESS;
}

void Engine::setWindowTitle(wchar_t *title)
{
	if (!device) return;
	device->setWindowCaption(title);
}

void Engine::run(void)
{
	if (!device) return;
	while(device->run())
    {
		sceneLoop();
    }
}
