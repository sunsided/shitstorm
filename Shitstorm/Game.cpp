#include "Game.h"
#include <math.h>

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
	cube = new CubeNode(5, 5, 5, 10, smgr->getRootSceneNode(), smgr, 666);
	ITexture *normalMap = driver->getTexture("textures\\crate.nm.jpg");
	driver->makeNormalMapTexture(normalMap, 1.0f);
	for(int i=0; i<cube->getMaterialCount(); ++i)
	{
		SMaterial *material = &cube->getMaterial(i);
		material->setTexture(0, driver->getTexture("textures\\crate.jpg"));
		material->setTexture(1, normalMap);
		// material->MaterialType = E_MATERIAL_TYPE::EMT_NORMAL_MAP_SOLID;
	}

	// Boden erzeugen
	plane = new PlaneNode(15, 15, 10, smgr->getRootSceneNode(), smgr, 667);
	plane->getMaterial(0).setTexture(0, driver->getTexture("textures\\wood.jpg"));

	// Lichter erzeugen
	cubeLights[0] = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
					video::SColorf(1.0f, 1.0F, 0.0F, 1.0F), 15.0f);
	cubeLights[1] = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
					video::SColorf(1.0f, 0.0F, 0.0F, 1.0F), 15.0f);

	return SUCCESS;
}

int Game::teardown() {
	return SUCCESS;
}

void Game::sceneLoop(int deltaT) {

	// Würfel rendern
	cube->setPosition(vector3df(0, 5, 0));
	cube->setRotation(vector3df(
		(float)(device->getTimer()->getTime() / 50 % 360), 
		(float)(device->getTimer()->getTime() / 20 % 360), 
		0.0F));

	// Lichter rendern
	cubeLights[0]->setPosition(vector3df(0, 0.25, 0));
	cubeLights[0]->setPosition(vector3df(
		(float)sin((device->getTimer()->getTime() / 50 % 360)/180.0F*3.141F)*5, 
		0.25F,
		(float)cos((device->getTimer()->getTime() / 50 % 360)/180.0F*3.141F)*5));

	cubeLights[1]->setPosition(vector3df(0, 0.25, 0));
	cubeLights[1]->setPosition(vector3df(
		(float)sin((device->getTimer()->getTime() / 50 % 360 + 180)/180.0F*3.141F)*5, 
		0.25F,
		(float)cos((device->getTimer()->getTime() / 50 % 360 + 180)/180.0F*3.141F)*5));

	// Boden rendern
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
