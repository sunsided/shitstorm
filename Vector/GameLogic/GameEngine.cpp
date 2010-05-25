/** 
 * Project Vector
 * Engine Base
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "GameEngine.h"

namespace pv {

	//! Erzeugt eine neue Instanz der GameEngine-Klasse.
	GameEngine::GameEngine(void)
	{
	}

	//! Destruktor.
	GameEngine::~GameEngine(void)
	{
	}

	//! Initialisiert die Spielschleife
	/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
		* ob die Hauptschleife durchlaufen werden soll.
		* @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
		*/
	bool GameEngine::OnPreSceneLoop(irr::f32 elapsedTime) { 
		if (!isPaused()) return true;

		getDevice()->yield();
		getDevice()->sleep(100, true);
		return false;
	}

	//! Implementierung der Haupt-Spielschleife
	void GameEngine::OnSceneLoop(irr::f32 elapsedTime) { 
		
		beginScene();
		renderScene();
		endScene();
	}

}