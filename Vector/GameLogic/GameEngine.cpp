/** 
 * Project Vector
 * Engine Base
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "GameEngine.h"
#include "SceneNodes/OrientationHelperSceneNode.h"

#include <iostream>

using namespace irr;

namespace pv {

	//! Erzeugt eine neue Instanz der GameEngine-Klasse.
	GameEngine::GameEngine(void)
		: renderTarget(NULL), renderTargetSceneManager(NULL),
		simpleEmitter(NULL), streamingBuffer(NULL)
	{
	}

	//! Destruktor.
	GameEngine::~GameEngine(void)
	{
	}

	//! Initialisiert die Engine
	/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
	EngineStatusCode GameEngine::OnSetupEngine() { 
		if(!getDriver()->queryFeature(video::EVDF_RENDER_TO_TARGET)) return ESC_FEATURE_FAILED;

		// Physikwelt erzeugen
		physics::PhysicsWorld *world = getPhysics()->createPhysicsWorld();
		if (!world) return ESC_PHYSICSWORLD_FAILED;

		// Zweiten Szenenmanager erzeugen
		renderTargetSceneManager = createAuxiliarySceneManager();
		if (!renderTargetSceneManager) return ESC_AUX_SMGR_FAILED;
		
		// Soundemitter erzeugen
		simpleEmitter = getSoundContext()->createSoundEmitter();
		streamingBuffer = getSoundDevice()->createStreamingBuffer();

		// Puffer registrieren
		simpleEmitter->attachBuffer(streamingBuffer);

		// Audiopuffer laden
		streamingAudioSource = new sound::OggVorbisAudioSource();
		if (!streamingAudioSource) return ESC_SOUND_FAILED;
		streamingAudioSource->openFile("OrbitalFunnyBreak.ogg");
		streamingAudioSource->attachToStreamingBuffer(streamingBuffer); // TODO: Emitter hier gleich mitsetzen!
		streamingAudioSource->initializeStreaming();
		//source.loadToBuffer(simpleBuffer);
		//source.closeFile();

		return ESC_SUCCESS; 
	}

	//! Initialisiert die Engine
	/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
	void GameEngine::OnTeardownEngine() {
		if (streamingAudioSource) {
			streamingAudioSource->closeFile();
			delete streamingAudioSource;
			streamingAudioSource = NULL;
		}
	}

	//! Initialisiert die Szene
	void GameEngine::OnSetupScene() {
		scene::ISceneManager *smgr = getSceneManager();
		scene::ISceneNode *rootNode = smgr->getRootSceneNode();




		// Hauptkamera erzeugen
		mainCamera = smgr->addCameraSceneNodeFPS(NULL, 100.0f, 0.01f);
		mainCamera->setNearValue(2.0f); // Ein Wert von null verursacht Probleme! -- UND: http://www.sjbaker.org/steve/omniv/love_your_z_buffer.html
		mainCamera->setPosition(core::vector3df(0, 10, -10));
		mainCamera->setTarget(core::vector3df(0, 0, 0));
		mainCamera->setName("Main Camera");




		// Ebene erzeugen
		testNode = new nodes::PlaneSceneNode(60, 60, 10, 10, 6.0f, 6.0f, rootNode, smgr, 10);
		testNode->setPosition(core::vector3df(0, 0, 0));
		testNode->getMaterial(0).Lighting = false;
		testNode->getMaterial(0).Wireframe = false;
		testNode->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\wood.jpg"));
		testNode->setName("Plane");
		
		// Physikalische Ebene erzeugen
		btCollisionShape* shape = new btBoxShape(btVector3(30, 0.1f, 30));
		getPhysics()->registerCollisionShape(shape);
		world::WorldObject* planeElement = world::WorldObjectFactory::Create(getPhysics()->getPhysicsWorld(0), testNode, shape, 0.0f, core::vector3df(0, 0, 0));
		planeElement->getPhysicsBody()->getAsRigidBody()->setFriction(1.25f);
		getWorld()->addWorldObject(planeElement);




		irr::f32 mass = 5.0f;

		// Ne Kiste
		scene::IMeshSceneNode *cube = smgr->addCubeSceneNode(3.0f, rootNode, 15);
		cube->setPosition(core::vector3df(0, 2.5, 2)); // TODO: Übernehmen lassen
		cube->getMaterial(0).Lighting = false;
		cube->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\crate.jpg"));
		cube->setVisible(true);
		//cube->addAnimator(smgr->createRotationAnimator(core::vector3df(0.05f, 0.3f,0)));
		cube->setName("Testwürfel 1");
		
		// Physikalische Kiste erzeugen
		shape = new btBoxShape(btVector3(1.5f, 1.5f, 1.5f));
		getPhysics()->registerCollisionShape(shape);
		world::WorldObject* cubeElement = world::WorldObjectFactory::Create(getPhysics()->getPhysicsWorld(0), cube, shape, mass, core::vector3df(0, 10, -2));
		cubeElement->getPhysicsBody()->setRotation(core::vector3df(10, 75, 0));
		getWorld()->addWorldObject(cubeElement);



		// Noch ne Kiste
		cube = smgr->addCubeSceneNode(3.0f, rootNode, 17);
		cube->getMaterial(0).Lighting = false;
		cube->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\crate.jpg"));
		cube->setVisible(true);
		cube->setName("Testwürfel 2");
		
		// Noch ne physikalische Kiste erzeugen
		// Das Box-Shape wird weiterverwendet
		cubeElement = world::WorldObjectFactory::Create(getPhysics()->getPhysicsWorld(0), cube, shape, mass, core::vector3df(-1, 15, -1));
		cubeElement->getPhysicsBody()->setRotation(core::vector3df(10, 75, 0));
		getWorld()->addWorldObject(cubeElement);



		// Und noch ne Kiste!
		cube = smgr->addCubeSceneNode(3.0f, rootNode, 18);
		cube->getMaterial(0).Lighting = false;
		cube->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\crate.jpg"));
		cube->setName("Testwürfel 4");
		
		// (Noch ne)² physikalische Kiste erzeugen
		// Das Box-Shape wird weiterverwendet
		cubeElement = world::WorldObjectFactory::Create(getPhysics()->getPhysicsWorld(0), cube, shape, mass, core::vector3df(0, 20, -2));
		cubeElement->getPhysicsBody()->setRotation(core::vector3df(0, -90, 0));
		getWorld()->addWorldObject(cubeElement);



		// Ne Kiste
		cube = smgr->addCubeSceneNode(3.0f, rootNode, 19);
		cube->getMaterial(0).Lighting = false;
		cube->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\crate.jpg"));
		cube->setName("Testwürfel 5");
		
		// Physikalische Kiste erzeugen
		cubeElement = world::WorldObjectFactory::Create(getPhysics()->getPhysicsWorld(0), cube, shape, mass, core::vector3df(-1.25, 1.5, -2));
		getWorld()->addWorldObject(cubeElement);




		// Orientierungshelfer erzeugen
		scene::ISceneNode *helper = new nodes::OrientationHelperSceneNode(1, renderTargetSceneManager->getRootSceneNode(), renderTargetSceneManager, 16);
		helper->setPosition(core::vector3df(0, 0.5f, 0));
		helper->setName("Debug Helper");

		// Render to texture: Textur
		renderTarget = getDriver()->addRenderTargetTexture(core::dimension2d<u32>(128,96), "RTT1");
		
		// Render to texture: Kamera
		renderTargetCamera = renderTargetSceneManager->addCameraSceneNode(NULL, core::vector3df(0, 0.8f, -3), core::vector3df(0, 0.8f, 0), -1);
		renderTargetCamera->setName("Render Target Camera");
		renderTargetCamera->setNearValue(0.01f);
		renderTargetCamera->setFarValue(6);




		// GUI-Element
		image = getGUIEnvironment()->addImage(core::rect<s32>(5, 5, 128+5, 96+5));
		image->setScaleImage(true);
		image->setUseAlphaChannel(true);


		// Musik starten
		simpleEmitter->play();
	}

	//! Initialisiert die Spielschleife
	/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
	* ob die Hauptschleife durchlaufen werden soll.
	* @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
	*/
	bool GameEngine::OnPreSceneLoop(f32 elapsedTime) { 
		if (!isPaused()) {

			static u32 lastFps = 0;
			u32 fps = getFps();
			if (fps != lastFps) {
				lastFps = fps;
				core::stringw text = L"Project Vector; ";
				text += fps;
				text += L" FPS";
				getDevice()->setWindowCaption(text.c_str());
			}

			return true;
		}

		getDevice()->yield();
		getDevice()->sleep(100, true);
		return false;
	}

	//! Handler für das Pause-Ereignis
	void GameEngine::OnPause() { 
		getTimer()->pause();

		// Musik anhalten
		simpleEmitter->pause();
	}

	//! Handler für das Unpause-Ereignis
	void GameEngine::OnUnpause() { 
		getTimer()->unpause(); 

		// Musik starten
		simpleEmitter->play();
	}

	//! Implementierung der Haupt-Spielschleife
	void GameEngine::OnSceneLoop(f32 elapsedTime) { 

		video::IVideoDriver *driver = getDriver();
		scene::ISceneManager *smgr = getSceneManager();

		// Musik aktualisieren
		getSoundDeviceManager()->updateStreamingAudio();

		// Physik aktualisieren
		updatePhysics(elapsedTime);

		// Szene beginnen
		beginScene();

		// Textur als Renderziel wählen
		driver->setRenderTarget(renderTarget, true, true, 0);

		// Rotation setzen und Szene rendern
		((nodes::OrientationHelperSceneNode*)renderTargetSceneManager->getSceneNodeFromId(16))->rotateZToDirection(mainCamera);
		renderScene(renderTargetSceneManager);

		// Backbuffer als Ziel wählen und Hauptszene rendern
		driver->setRenderTarget(video::ERT_FRAME_BUFFER, true, true, getClearColor());
		renderScene();

		// Käfig um die Kamera zeichnen
		//drawCameraOrientationCage(mainCamera);

		// Das Bild zeigen
		image->setImage(renderTarget);
		renderGui();

		// Szene beenden
		endScene();
	}

}