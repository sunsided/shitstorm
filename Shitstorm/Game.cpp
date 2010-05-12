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

void Game::sceneLoop() {
	driver->beginScene(true, true, SColor(255, 64, 64, 64));

    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
}
