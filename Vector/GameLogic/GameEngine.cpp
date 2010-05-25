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
	{
	}

	//! Destruktor.
	GameEngine::~GameEngine(void)
	{
	}

	//! Initialisiert die Szene
	void GameEngine::OnSetupScene() {
		scene::ICameraSceneNode *camera = getSceneManager()->addCameraSceneNodeFPS();
		camera->setPosition(core::vector3df(0, 0, -10));
		camera->setNearValue(0);

		// getSceneManager()->addCubeSceneNode();
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
		
		beginScene();

		/*
		video::IVideoDriver *driver = getDriver();
		scene::ISceneManager *smgr = getSceneManager();
		scene::ISceneCollisionManager *cmgr = smgr->getSceneCollisionManager();

		video::SMaterial material;
		material.Lighting = false;
		material.Thickness = 1.0f;

		core::line3df ray = cmgr->getRayFromScreenCoordinates(core::vector2d<s32>(320, 240));
		core::vector3df lookDirection = ray.getVector();
		core::vector3df base = ray.start + 2*lookDirection;
		std::cout << "Base: " << ray.end.X << ", " << ray.end.Y << ", " << ray.end.Z << std::endl;

		scene::ICameraSceneNode *camera = smgr->getActiveCamera();
		core::vector3df up = camera->getUpVector();

		driver->setMaterial(material);
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DLine(base, base+core::vector3df(0,0.5,0), video::SColor(255, 0, 255, 0));
		driver->draw3DLine(base, base+core::vector3df(0.5,0,0), video::SColor(255, 255, 0, 0));
		driver->draw3DLine(base, base+core::vector3df(0,0,0.5), video::SColor(255, 0, 0, 255));
		*/

		// Würfel um die Kamera zeichnen
		drawCameraOrientationCage();

		renderScene();
		endScene();
	}

}