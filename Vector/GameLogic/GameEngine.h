/** 
 * Project Vector
 * Game Engine
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include "global.h"
#include "EngineBase.h"
#include "SceneNodes/PlaneSceneNode.h"
#include "World/WorldElementFactory.h"

namespace pv {

	//! Die Spiele-Engine
	class GameEngine : public EngineBase
	{
	public:

		//! Erzeugt eine neue Instanz der GameEngine-Klasse.
		GameEngine(void);

		//! Destruktor.
		~GameEngine(void);

	protected:

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		EngineStatusCode OnSetupEngine();

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		void OnTeardownEngine() {}

		//! Initialisiert die Szene
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual void OnSetupScene();

		//! Initialisiert die Spielschleife
		/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
		 * ob die Hauptschleife durchlaufen werden soll.
		 * @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
		 */
		inline bool OnPreSceneLoop(irr::f32 elapsedTime);

		//! Implementierung der Haupt-Spielschleife
		void OnSceneLoop(irr::f32 elapsedTime);

		//! Handler für das Pause-Ereignis
		void OnPause() { getTimer()->pause(); }

		//! Handler für das Unpause-Ereignis
		void OnUnpause() { getTimer()->unpause(); }

	private:

		//! Die Hauptkamera
		irr::scene::ICameraSceneNode *mainCamera;

		//! Knoten für Testzwecke
		nodes::PlaneSceneNode *testNode;

		//! Zieltextur für render to texture
		irr::video::ITexture* renderTarget;

		//! Kamera für render to texture
		irr::scene::ICameraSceneNode *renderTargetCamera;

		//! GUI-Element, das die Textur anzeigt
		gui::IGUIImage *image;

		//! Testelement
		world::WorldElement* cubeElement;

		//! Noch ein Testelement
		world::WorldElement* planeElement;
	};

}

#endif