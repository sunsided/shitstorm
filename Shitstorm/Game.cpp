#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
}

int Game::setup() {
	setWindowTitle(L"Project Shitstorm");

	device->getCursorControl()->setVisible(false);

	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
	camera->setPosition(vector3df(10, 0, 10));
	camera->setTarget(vector3df(0, 0, 0));

	//camera = smgr->addCameraSceneNode(0, vector3df(10, -10, 10), vector3df(0, 0, 0));
	cube = new CubeNode(5, 5, 5, smgr->getRootSceneNode(), smgr, 666);

	return SUCCESS;
}

void Game::sceneLoop(int deltaT) {

	core::stringw tmp(L"Project Shitstorm [");
    tmp += driver->getName();
    tmp += L"] fps: ";
	tmp += getFps();
    setWindowTitle(tmp.c_str());

	smgr->registerNodeForRendering(cube);
	cube->setPosition(vector3df(0, 0, 0));
	cube->setRotation(vector3df(
		device->getTimer()->getTime() / 50 % 360, 
		device->getTimer()->getTime() / 20 % 360, 
		0));

	driver->beginScene(true, true, SColor(255, 64, 64, 64));

    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
}
