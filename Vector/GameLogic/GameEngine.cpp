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

		// Hauptkamera erzeugen
		mainCamera = smgr->addCameraSceneNodeFPS(NULL, 100.0f, 0.01f);
		mainCamera->setNearValue(0.1f); // Ein Wert von null verursacht Probleme!
		mainCamera->setPosition(vector3df(0, 10, -10));
		mainCamera->setTarget(core::vector3df(0, 0, 0));
		mainCamera->setName("Main Camera");

		// Ebene erzeugen
		testNode = new nodes::PlaneSceneNode(20, 10, rootNode, smgr, 10);
		testNode->setPosition(core::vector3df(0, 0, 0));
		testNode->getMaterial(0).Lighting = false;
		testNode->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\wood.jpg"));
		testNode->setName("Plane");

		// Ne Kiste
		scene::IMeshSceneNode *cube = smgr->addCubeSceneNode(3.0f, rootNode, 15);
		cube->setPosition(core::vector3df(0, 1.5, 2));
		cube->getMaterial(0).Lighting = false;
		cube->getMaterial(0).setTexture(0, getDriver()->getTexture("textures\\crate.jpg"));
		cube->setVisible(true);
		cube->setName("Testwürfel");

		scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.0f, 0.3f,0));
		cube->addAnimator(anim);
		
		// Render to texture: Textur
		renderTarget = getDriver()->addRenderTargetTexture(core::dimension2d<u32>(160,120), "RTT1");
		
		// Render to texture: Kamera
		renderTargetCamera = smgr->addCameraSceneNode(NULL, core::vector3df(0, 2, -5), core::vector3df(0, 0, 0), -1);
		renderTargetCamera->setName("Render Target Camera");
		renderTargetCamera->setNearValue(0.1f);
		renderTargetCamera->setFarValue(20);
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

		// Szene beginnen
		beginScene();

		// Textur als Renderziel wählen
		driver->setRenderTarget(renderTarget, true, true, video::SColor(4,64,16,0));
		smgr->setActiveCamera(renderTargetCamera);

		// Würfel einblenden
		renderScene();

		// Würfel holen
		scene::ISceneNode *cube = smgr->getSceneNodeFromId(15);
		driver->setMaterial(getUnlitMaterial());
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DBox(cube->getTransformedBoundingBox());

		// Backbuffer als Ziel wählen
		driver->setRenderTarget(video::ERT_FRAME_BUFFER, true, true, getClearColor());
		smgr->setActiveCamera(mainCamera);

		// Szene erneut rendern
		renderScene();

		// Bounding Box zeichnen
		driver->setMaterial(getUnlitMaterial());
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DBox(cube->getTransformedBoundingBox());

		// Käfig um die Kamera zeichnen
		drawCameraOrientationCage(mainCamera);

		// Das Bild zeigen
		gui::IGUIImage *image = getGUIEnvironment()->addImage(core::rect<s32>(5, 5, 165, 125));
		image->setScaleImage(true);
		image->setUseAlphaChannel(true);
		image->setImage(renderTarget);
		renderGui();

		// Szene beenden
		endScene();
	}

}