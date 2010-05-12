#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
}

int Game::setup() {
	setWindowTitle(L"Project Shitstorm");
	return SUCCESS;
}

void Game::sceneLoop(int deltaT) {

	core::stringw tmp(L"Project Shitstorm [");
    tmp += driver->getName();
    tmp += L"] fps: ";
	tmp += getFps();
    setWindowTitle(tmp.c_str());


	driver->beginScene(true, true, SColor(255, 64, 64, 64));
	
	device->sleep(2);

    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
}
