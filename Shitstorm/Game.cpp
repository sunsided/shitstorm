#include "Game.h"
#include <math.h>

#include "SpatialObject.h"

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
	PF->SelectEngine("Bullet");
	physics = PF->CreatePhysics();
	if (physics) {
		palPhysicsDesc desc;
		desc.m_vGravity = palVector3(0, -9.8, 0);
		physics->Init(desc);
	}
	else {
		printf("Physikengine konnte nicht initialisiert werden.");
		return -1;
	}

	// Würfel erzeugen
	physicsBox = PF->CreateBox();
	if (physicsBox) physicsBox->Init(0, 5, 0, 5, 5, 7, 10);

	// Boden erzeugen
	physicsPlane = PF->CreateTerrainPlane();
	if (physicsPlane) physicsPlane->Init(0, 0, 0, 15);

	return SUCCESS;
}

int Game::teardown() {

	// Physikengine beenden
	if (physics) physics->Cleanup();

	return SUCCESS;
}

void Game::setupLoop() {

	// Physik vorwärmen
	physics->Update(0.0f);
}

void Game::sceneLoop(int deltaT) {

	f32 deltaTInSeconds = deltaT * 0.001F;

	static SpatialObject foo = SpatialObject(vector3df(0, 5, 0));
	static bool enableRotation = false;
	static bool physicsEnabled = true;

	// Physik aktualisieren
	if (physics) {
		if (physicsEnabled) physics->Update(deltaTInSeconds);
		palMatrix4x4 matrix = physicsBox->GetLocationMatrix();
		matrix4 mat;
		memcpy(&mat[0], matrix._mat, sizeof(f32)*4*4);
		foo.setPosition(mat.getTranslation());
		cube->setRotation(mat.getRotationDegrees());
	}

	// Schleife beenden
	if(eventReceiver.keyPressed(KEY_ESCAPE)) {
		device->closeDevice();
		return;
	}
	
	// Kistenposition ermitteln
	palVector3 location;
	physicsBox->GetPosition(location);

	// Im nächsten Durchgang gibt's wieder Physik
	physicsEnabled = true;

	// Kiste bewegen
	if(eventReceiver.keyDown(KEY_UP)) {
		physicsEnabled = false;

		if(eventReceiver.keyDown(KEY_LSHIFT) || eventReceiver.keyDown(KEY_SHIFT) || eventReceiver.keyDown(KEY_RSHIFT))
			location.y += 0.01;
		else
			location.z += 0.01;
	}
	if(eventReceiver.keyDown(KEY_DOWN)) {
		physicsEnabled = false;

		if(eventReceiver.keyDown(KEY_LSHIFT) || eventReceiver.keyDown(KEY_SHIFT) || eventReceiver.keyDown(KEY_RSHIFT))
			location.y -= 0.01;
		else
			location.z -= 0.01;
	}
	if(eventReceiver.keyDown(KEY_LEFT)) {
		physicsEnabled = false;
		location.x -= 0.01;
	}
	if(eventReceiver.keyDown(KEY_RIGHT)) {
		physicsEnabled = false;
		location.x += 0.01;
	}

	// Kistenposition setzen
	physicsBox->SetPosition(location.x, location.y, location.z);

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
	foo.update(deltaTInSeconds);

	// Würfel rendern
	//cube->setPosition(vector3df(cubeX, cubeY, cubeZ));
	cube->setPosition(foo.getPosition());

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
