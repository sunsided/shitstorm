#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
}

int Game::setup() {
	setWindowTitle(L"Project Shitstorm");

	// Mauszeiger ausblenden
	device->getCursorControl()->setVisible(false);

	// Kamera erzeugen
	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
	camera->setPosition(vector3df(0, 10, -10)); // 10 oben, 10 zurück (aus dem Bildschirm heraus)
	camera->setTarget(vector3df(0, 0, 0));

	// Würfel erzeugen
	cube = new CubeNode(5, 5, 5, smgr->getRootSceneNode(), smgr, 666);
	
	cubeLights = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
                video::SColorf(1.0f, 1.0F, 0.0F, 0.0F), 15.0f);


	// Boden erzeugen
	plane = new PlaneNode(15, 15, smgr->getRootSceneNode(), smgr, 667);
	plane->getMaterial(0).setTexture(0, driver->getTexture("textures\\wood.jpg"));

	return SUCCESS;
}

void Game::sceneLoop(int deltaT) {

	// Würfel rendern
	smgr->registerNodeForRendering(cube);
	cube->setPosition(vector3df(0, 5, 0));
	cube->setRotation(vector3df(
		(float)(device->getTimer()->getTime() / 50 % 360), 
		(float)(device->getTimer()->getTime() / 20 % 360), 
		0.0F));

	// Lichter rendern
	smgr->registerNodeForRendering(cubeLights);
	cubeLights->setPosition(vector3df(-10, 0, 0));
	/*
	cubeLights->setRotation(vector3df(
		(float)(device->getTimer()->getTime() / 50 % 360), 
		(float)(device->getTimer()->getTime() / 20 % 360), 
		0.0F));
	*/

	// Boden rendern
	smgr->registerNodeForRendering(plane);
	plane->setPosition(vector3df(0, 0, 0));
	
	// Licht durchcyclen
	/*
	float lightValue = (device->getTimer()->getTime() / 100 % 200)/100.0F;
	if(lightValue > 1) lightValue = 1.0F - lightValue;
	*/
	float lightValue = 0.15f;
	smgr->setAmbientLight(SColorf(lightValue, lightValue, lightValue));

	// Szene rendern
	driver->beginScene(true, true, SColor(255, 64, 64, 64));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
}
