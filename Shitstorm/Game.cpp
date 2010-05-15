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
	camera->setPosition(vector3df(0, 10, -10)); // 10 oben, 10 zurück (aus dem Bildschirm heraus)
	camera->setTarget(vector3df(0, 0, 0));

	//camera = smgr->addCameraSceneNode(0, vector3df(10, -10, 10), vector3df(0, 0, 0));
	cube = new CubeNode(5, 5, 5, smgr->getRootSceneNode(), smgr, 666);

	plane = new PlaneNode(15, 15, smgr->getRootSceneNode(), smgr, 666);
	plane->getMaterial(0).setTexture(0, driver->getTexture("textures\\wood.jpg"));

	return SUCCESS;
}

void Game::sceneLoop(int deltaT) {

	core::stringw tmp(L"Project Shitstorm [");
    tmp += driver->getName();
    tmp += L"] fps: ";
	tmp += getFps();
    setWindowTitle(tmp.c_str());

	smgr->registerNodeForRendering(cube);
	cube->setPosition(vector3df(0, 5, 0));
	cube->setRotation(vector3df(
		(float)(device->getTimer()->getTime() / 50 % 360), 
		(float)(device->getTimer()->getTime() / 20 % 360), 
		0.0F));

	smgr->registerNodeForRendering(plane);
	plane->setPosition(vector3df(0, 0, 0));
	
	smgr->setAmbientLight(SColorf(.5F, .5F, .5F));

	driver->beginScene(true, true, SColor(255, 64, 64, 64));

    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
}
