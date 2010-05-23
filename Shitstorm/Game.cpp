#include "Game.h"
#include "SpatialObject.h"

#include <math.h>
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, "libpald.lib")
#pragma comment(lib, "libpal_bulletd.lib")
#else
#pragma comment(lib, "libpal.lib")
#pragma comment(lib, "libpal_bullet.lib")
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

	// Kleinen Würfel erzeugen
	tinyCube = new CubeNode(2, 1, 4, 4, smgr->getRootSceneNode(), smgr, 766);
	for(int i=0; i<tinyCube->getMaterialCount(); ++i)
	{
		SMaterial *material = &tinyCube->getMaterial(i);
		material->setTexture(0, driver->getTexture("textures\\wood.jpg"));
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
	cubeLights[0]->enableCastShadow(true);
	cubeLights[1] = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
					video::SColorf(1.0f, 0.0F, 0.0F, 1.0F), 10.0f);
	cubeLights[1]->enableCastShadow(true);

	// Ambientes Licht
	smgr->setAmbientLight(SColorf(0.09f, 0.09f, 0.09f));

	// Physikengine laden
	cout << "Initialisiere Physikengine ..." << endl;
	PF->LoadPALfromDLL(); 
	PF->SelectEngine("Bullet");
	physics = PF->CreatePhysics();
	if (physics) {
		palPhysicsDesc desc;
		desc.m_vGravity = palVector3(palPhysicsDesc::DEFAULT_GRAVITY_X, palPhysicsDesc::DEFAULT_GRAVITY_Y, palPhysicsDesc::DEFAULT_GRAVITY_X);
		physics->Init(desc);

		cout << "Physikengine initialisiert." << endl;
	}
	else {
		cout << "Physikengine konnte nicht initialisiert werden." << endl;
		return -1;
	}

	// Materialien
	palMaterials *materials = PF->CreateMaterials();
	palMaterialDesc matDesc;
	matDesc.m_fStatic = 0.75f;
	matDesc.m_fKinetic = 0.5f;
	matDesc.m_fRestitution = 0.01f;
	matDesc.m_bEnableAnisotropicFriction = true;
	materials->NewMaterial("wood", matDesc);

	// Würfel erzeugen
	physicsBox = PF->CreateBox();
	if (physicsBox) {
		physicsBox->Init(0, 5, 0, 5, 5, 6, 1000);
		physicsBox->SetMaterial(materials->GetMaterial("wood"));
		physicsBox->SetOrientation(30*DEG2RAD, 30*DEG2RAD, 0.0f);
		physicsBox->SetSkinWidth(0.2);
	}

	// Kleinen Würfel erzeugen
	tinyPhysicsBox = PF->CreateBox();
	if (tinyPhysicsBox) {
		tinyPhysicsBox->Init(-3, 0.5, -2.3, 2, 1, 4, 10);
		tinyPhysicsBox->SetMaterial(materials->GetMaterial("wood"));
		tinyPhysicsBox->SetSkinWidth(0.1);
	}

	// Boden erzeugen
	physicsPlane = PF->CreateTerrainPlane();
	if (physicsPlane) {
		physicsPlane->Init(0, 0, 0, 15);
		// physicsPlane->SetMaterial(materials->GetMaterial("wood"));
	}

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

void Game::sceneLoop(f32 deltaT, bool windowIsActive) {

	static SpatialObject foo = SpatialObject(vector3df(0, 5, 0));
	static bool enableRotation = false;
	static bool boxNeedsUpdating = true;
	static bool pausePhysics = false;

	// Spiel anhalten
	if (!windowIsActive) {
		timer->pause();
		device->yield();
		return;
	}
	timer->unpause();

	// Schleife beenden
	if(eventReceiver.keyPressed(KEY_KEY_P)) {
		pausePhysics = !pausePhysics;
	}

	// Schleife beenden
	if(eventReceiver.keyPressed(KEY_ESCAPE)) {
		device->closeDevice();
		return;
	}

	// Schleife beenden
	if(eventReceiver.keyPressed(KEY_KEY_R)) {
		physicsBox->SetPosition(0, 6, 0);
		physicsBox->SetOrientation(0, (device->getTimer()->getRealTime() % 360) * DEGTORAD, ((device->getTimer()->getRealTime() % 50) - 15) * DEGTORAD);
		physicsBox->SetAngularVelocity(palVector3(0, 0, 0));
		physicsBox->SetLinearVelocity(palVector3(0, 0, 0));
		physicsBox->SetActive(true);

		tinyPhysicsBox->SetPosition(-3, 0.5, -2.3);
		tinyPhysicsBox->SetOrientation(0, ((device->getTimer()->getRealTime() % 50) - 25) * DEGTORAD, 0);
		tinyPhysicsBox->SetAngularVelocity(palVector3(0, 0, 0));
		tinyPhysicsBox->SetLinearVelocity(palVector3(0, 0, 0));
		tinyPhysicsBox->SetActive(true);
	}
		
	// Kistenposition ermitteln
	palVector3 location;
	physicsBox->GetPosition(location);

	// Box muss nicht aktualisiert werden
	boxNeedsUpdating = false;
	bool physicsEnabled = !pausePhysics;

	// Kiste bewegen
	if(eventReceiver.keyDown(KEY_UP)) {
		boxNeedsUpdating = true;
		physicsEnabled = false;

		if(eventReceiver.keyDown(KEY_LSHIFT) || eventReceiver.keyDown(KEY_SHIFT) || eventReceiver.keyDown(KEY_RSHIFT))
			location.y += 0.01;
		else
			location.z += 0.01;
	}
	if(eventReceiver.keyDown(KEY_DOWN)) {
		boxNeedsUpdating = true;
		physicsEnabled = false;

		if(eventReceiver.keyDown(KEY_LSHIFT) || eventReceiver.keyDown(KEY_SHIFT) || eventReceiver.keyDown(KEY_RSHIFT))
			location.y -= 0.01;
		else
			location.z -= 0.01;
	}
	if(eventReceiver.keyDown(KEY_LEFT)) {
		boxNeedsUpdating = true;
		physicsEnabled = false;
		location.x -= 0.01;
	}
	if(eventReceiver.keyDown(KEY_RIGHT)) {
		boxNeedsUpdating = true;
		physicsEnabled = false;
		location.x += 0.01;
	}

	// Kistenposition setzen
	if (boxNeedsUpdating) {
		physicsBox->SetPosition(location.x, location.y, location.z);
		physicsBox->SetActive(true);
	}

	// Physik aktualisieren
	if (physics) {
		if (physicsEnabled) physics->Update(deltaT);
		palMatrix4x4 matrix = physicsBox->GetLocationMatrix();
		matrix4 mat;
		memcpy(&mat[0], matrix._mat, sizeof(f32)*4*4);
		foo.setPosition(mat.getTranslation());
		cube->setRotation(mat.getRotationDegrees());

		matrix = tinyPhysicsBox->GetLocationMatrix();
		memcpy(&mat[0], matrix._mat, sizeof(f32)*4*4);
		tinyCube->setPosition(mat.getTranslation());
		tinyCube->setRotation(mat.getRotationDegrees());
	}

	// FOV der Kamera ändern - Zoomen
	camera->setFOV(min<f32>(PI - 0.005f, max<f32>(0.005f, camera->getFOV() - eventReceiver.mouseWheel() * 0.05f)));
	if(eventReceiver.middleMousePressed()) camera->setFOV(1.256637f);

	// Position des SpatialObjects aktualisieren
	foo.update(deltaT);

	// Würfel rendern
	//cube->setPosition(vector3df(cubeX, cubeY, cubeZ));
	cube->setPosition(foo.getPosition());

	// Lichter rendern
	cubeLights[0]->setPosition(vector3df(
		(float)sin(((device->getTimer()->getTime() / 50 + 90) % 360)/180.0F*3.141F)*7, 
		0.25F,
		(float)cos(((device->getTimer()->getTime() / 50 + 90) % 360)/180.0F*3.141F)*7));

	cubeLights[1]->setPosition(vector3df(
		(float)sin((device->getTimer()->getTime() / 50 % 360 + 270)/180.0F*3.141F)*2, 
		14.25F,
		(float)cos((device->getTimer()->getTime() / 50 % 360 + 270)/180.0F*3.141F)*2));
	
	// Boden rendern
	plane->setPosition(vector3df(0, 0, 0));

	// Szene rendern
	driver->beginScene(true, true, SColor(255, 64, 64, 64));
    smgr->drawAll();

	// GUI säubern
	guienv->clear();

	core::stringw text = L"FPS: ";
	text += getFps();
	text += L"\r\nCamera rot: ";
	text += camera->getRotation().X;
	text += L", ";
	text += camera->getRotation().Y;
	text += L", ";
	text += camera->getRotation().Z;
	text += L"\r\nCamera FOV: ";
	text += camera->getFOV();
	text += L"\r\nPhysics: ";
	text += physics->GetVersion();
	text += L"\r\nPhysics time: ";
	text += physics->GetTime();
	text += L"\r\nPhysics timestep: ";
	text += physics->GetLastTimestep();
	
	palVector3 gravity;
	physics->GetGravity(gravity);

	text += L"\r\nPhysics gravity: ";
	text += gravity.x;
	text += L", ";
	text += gravity.y;
	text += L", ";
	text += gravity.z;

	text += L"\r\nPhysics box: ";
	text += physicsBox->IsActive() ? "active" : "resting";

	guienv->addStaticText(text.c_str(), rect<int>(5,5, getScreenSize().Width - 5, getScreenSize().Height - 5), false, false);
    guienv->drawAll();


    driver->endScene();
}
