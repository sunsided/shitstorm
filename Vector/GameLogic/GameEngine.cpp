/** 
 * Project Vector
 * Engine Base
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "GameEngine.h"

#include <iostream>

using namespace irr;

namespace pv {

	//! Erzeugt eine neue Instanz der GameEngine-Klasse.
	GameEngine::GameEngine(void)
		: renderTarget(NULL)
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
		return ESC_SUCCESS; 
	}

	//! Initialisiert die Szene
	void GameEngine::OnSetupScene() {
		scene::ISceneManager *smgr = getSceneManager();
		scene::ISceneNode *rootNode = smgr->getRootSceneNode();

		mainCamera = smgr->addCameraSceneNodeFPS(NULL, 100.0f, 0.01f);
		mainCamera->setPosition(vector3df(0, 1, -1));
		mainCamera->setTarget(core::vector3df(0, 0, 0));
		mainCamera->setNearValue(0);
		mainCamera->setFarValue(1000);
		mainCamera->setName("Main Camera");

		// Ebene erzeugen
		testNode = new PlaneNode(10, 4, rootNode, smgr, 10);
		testNode->getMaterial(0).Lighting = false;
		/*
		testNode->getMaterial(0).FrontfaceCulling = false;
		testNode->getMaterial(0).BackfaceCulling = false;
		*/
		testNode->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\wood.jpg"));
		testNode->setName("Plane");

		// Ne Kiste
		scene::IMeshSceneNode *cube = smgr->addCubeSceneNode(1.0f, rootNode, 15);
		cube->setPosition(core::vector3df(0, 0, 5));
		cube->getMaterial(0).Lighting = false;
		cube->setVisible(true);
		cube->setName("Testwürfel");

		// Ambientes Licht
		smgr->setAmbientLight(SColorf(0.09f, 0.09f, 0.09f));

		// Render to texture: Textur
		renderTarget = getDriver()->addRenderTargetTexture(core::dimension2d<u32>(256,256), "RTT1");
		
		// Render to texture: Kamera
		renderTargetCamera = smgr->addCameraSceneNode(NULL, core::vector3df(0, 0, -5), core::vector3df(0, 0, 100), -1, false);
		renderTargetCamera->setName("Render Target Camera");

		// Hauptkamera auswählen
		smgr->setActiveCamera(mainCamera);
	}

	//! Initialisiert die Spielschleife
	/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
		* ob die Hauptschleife durchlaufen werden soll.
		* @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
		*/
	bool GameEngine::OnPreSceneLoop(f32 elapsedTime) { 
		if (!isPaused()) return true;

		getDevice()->yield();
		getDevice()->sleep(100, true);
		return false;
	}

	//! Implementierung der Haupt-Spielschleife
	void GameEngine::OnSceneLoop(f32 elapsedTime) { 

		video::IVideoDriver *driver = getDriver();
		scene::ISceneManager *smgr = getSceneManager();

		std::cout << mainCamera->getRotation().X << ", "<< mainCamera->getRotation().Y << ", "<< mainCamera->getRotation().Z <<  " --- " <<
			mainCamera->getPosition().X << ", "<< mainCamera->getPosition().Y << ", "<< mainCamera->getPosition().Z << std::endl;

		beginScene();

		// Würfel holen
		scene::ISceneNode *cube = smgr->getSceneNodeFromId(15);

		// Renderziel wählen
		driver->setRenderTarget(renderTarget, true, true, video::SColor(5,0,0,255));
		smgr->setActiveCamera(renderTargetCamera);

		driver->setMaterial(getUnlitMaterial());
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DBox(core::aabbox3d<f32>(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f));

		// Würfel einblenden
		cube->setVisible(true);
		renderScene();

		// Backbuffer als Ziel wählen
		driver->setRenderTarget(video::ERT_FRAME_BUFFER, true, true, 0); // getClearColor());
		smgr->setActiveCamera(mainCamera);

		// Würfel ausblenden
		cube->setVisible(false);
		renderScene();

		// Käfig um die Kamera zeichnen
		drawCameraOrientationCage(mainCamera);

		// Das Bild zeigen
		gui::IGUIImage *image = getGUIEnvironment()->addImage(core::rect<s32>(5, 5, 105, 105));
		image->setUseAlphaChannel(true);
		image->setImage(renderTarget);
		renderGui();

		// Szene beenden
		endScene();
	}

}