#include "Game.h"
#include <math.h>

#include "SpatialObject.h"

#include "pal/palFactory.h"
#if _DEBUG
#pragma comment(lib, "libpald.lib")
#else
#pragma comment(lib, "libpal.lib")
#endif

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
	cube = new CubeNode(5, 5, 7, 4, smgr->getRootSceneNode(), smgr, 666);
	ITexture *normalMap = driver->getTexture("textures\\crate.nm.jpg");
	driver->makeNormalMapTexture(normalMap, 10.0f);
	for(int i=0; i<cube->getMaterialCount(); ++i)
	{
		SMaterial *material = &cube->getMaterial(i);
		material->setTexture(0, driver->getTexture("textures\\crate.jpg"));
		material->setTexture(1, normalMap);
		material->MaterialType = EMT_NORMAL_MAP_SOLID;
	}

	// Boden erzeugen
	plane = new PlaneNode(15, 15, 4, smgr->getRootSceneNode(), smgr, 667);
	plane->getMaterial(0).setTexture(0, driver->getTexture("textures\\wood2.jpg"));
	normalMap = driver->getTexture("textures\\wood2.nm.jpg");
	driver->makeNormalMapTexture(normalMap, 20.0f);
	plane->getMaterial(0).setTexture(1, normalMap);

	// Lichter erzeugen
	cubeLights[0] = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
					video::SColorf(1.0f, 1.0F, 0.0F, 1.0F), 15.0f);
	cubeLights[1] = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
					video::SColorf(1.0f, 0.0F, 0.0F, 1.0F), 10.0f);

	// Physikengine laden
	PF->LoadPALfromDLL(); 


	return SUCCESS;
}

int Game::teardown() {
	return SUCCESS;
}

void Game::sceneLoop(int deltaT) {

	static float cubeX = 0, cubeY = 5, cubeZ = 0;
	static SpatialObject foo = SpatialObject(vector3df(0, 5, 0));
	static bool enableRotation = false;

	// Schleife beenden
	if(eventReceiver.keyPressed(KEY_ESCAPE)) {
		device->closeDevice();
		return;
	}

	// Kiste drehen
	if(eventReceiver.keyPressed(KEY_KEY_R)) {
		enableRotation = !enableRotation;
	}

	// Kiste bewegen
	if(eventReceiver.keyDown(KEY_UP)) {
		foo.addAcceleration(0, 0, 0.01);
	}
	if(eventReceiver.keyDown(KEY_DOWN)) {
		foo.addAcceleration(0, 0, -0.01);
	}
	if(eventReceiver.keyDown(KEY_LEFT)) {
		foo.addAcceleration(-0.01, 0, 0);
	}
	if(eventReceiver.keyDown(KEY_RIGHT)) {
		foo.addAcceleration(0.01, 0, 0);
	}

	// FOV der Kamera ändern - Zoomen
	/*
	if(eventReceiver.keyDown(KEY_ADD) || eventReceiver.keyDown(KEY_PLUS)) {
		camera->setFOV(camera->getFOV() + 0.01);
	}
	if(eventReceiver.keyDown(KEY_SUBTRACT) || eventReceiver.keyDown(KEY_MINUS)) {
		camera->setFOV(camera->getFOV() - 0.01);
	}
	*/

	// Position des SpatialObjects aktualisieren
	foo.update(deltaT * 0.0001F);

	// Würfel rendern
	//cube->setPosition(vector3df(cubeX, cubeY, cubeZ));
	cube->setPosition(foo.getPosition());
	
	if(enableRotation) {
		cube->setRotation(vector3df(
			(float)(device->getTimer()->getTime() / 50 % 360), 
			(float)(device->getTimer()->getTime() / 20 % 360), 
			0.0f));
	}

	// Lichter rendern
	cubeLights[0]->setPosition(vector3df(
		(float)sin((device->getTimer()->getTime() / 50 % 360)/180.0F*3.141F)*5, 
		0.25F,
		(float)cos((device->getTimer()->getTime() / 50 % 360)/180.0F*3.141F)*5));

	cubeLights[1]->setPosition(vector3df(
		(float)sin((device->getTimer()->getTime() / 50 % 360 + 270)/180.0F*3.141F)*2, 
		14.25F,
		(float)cos((device->getTimer()->getTime() / 50 % 360 + 270)/180.0F*3.141F)*2));

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
