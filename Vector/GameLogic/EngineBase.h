/** 
 * Project Vector
 * Engine Base
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#ifndef _ENGINEBASE_H
#define _ENGINEBASE_H
#pragma once

#include "global.h"
#include "EngineStatusCode.h"
#include "EngineInitializationParams.h"
#include "GameTimer.h"

namespace pv {

	//! Basisklasse der Spiele-Engine.
	class EngineBase
	{
	public:

		//! Erzeugt eine neue Instanz der CEngineBase-Klasse.
		EngineBase(void) :
		  irrlichtDevice(NULL), sceneManager(NULL), videoDriver(NULL), guiEnvironment(NULL), engineClean(true), timer(NULL)
		{}

		//! Destruktor.
		virtual ~EngineBase(void);

		//! Initialisiert die Engine
		/** Initialisiert die Engine mit den gegebenen Parametern.
		 * @param params	Grundeinstellungen der Engine
		 * @returns			Statuscode; Im Erfolgsfall EST_SUCCESS
		 */
		EngineStatusCode initialize(EngineInitializationParams &params);

		//! Startet die Haupt-Spielschleife
		EngineStatusCode run();

	private:

		//! Schließt die Engine
		void close();

	protected:

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual EngineStatusCode setupEngine() = 0;

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual void teardownEngine() = 0;

		//! Initialisiert die Spielschleife
		/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
		 * ob die Hauptschleife durchlaufen werden soll.
		 * @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
		 */
		inline virtual bool preSceneLoop(irr::f32 elapsedTime) { return true; }

		//! Implementierung der Haupt-Spielschleife
		virtual void sceneLoop(irr::f32 elapsedTime) = 0;

		//! Ermittelt die FPS
		inline irr::u32 getFps() const { return videoDriver ? videoDriver->getFPS() : 0; }

		//! Bezieht das IrrlichtDevice
		inline irr::IrrlichtDevice* getDevice() const { return irrlichtDevice; }

		//! Bezieht den Videotreiber
		inline irr::video::IVideoDriver* getDriver() const { return videoDriver; }

		//! Bezieht den Szenenmanager
		inline irr::scene::ISceneManager* getSceneManager() const { return sceneManager; }

		//! Bezieht die GUI-Umgebung
		inline irr::gui::IGUIEnvironment* getGUIEnvironment() const { return guiEnvironment; }

	private:

		//! Ermittelt den Videotreiber
		/**
		 * @param driverHint	Der vom Benutzer gewählte Treiber
		 * @returns				Der von der Irrlicht-Engine zu verwendende Treiber
		 */
		irr::video::E_DRIVER_TYPE selectVideoDriver(VideoDriver driverHint) const;

	private:

		//! Das Irrlicht-Device
		irr::IrrlichtDevice* irrlichtDevice;

		//! Der Videotreiber
		irr::video::IVideoDriver* videoDriver;

		//! Der Szenenmanager
		irr::scene::ISceneManager* sceneManager;

		//! Die GUI
		irr::gui::IGUIEnvironment* guiEnvironment;

		//! Gibt an, ob die Engine aufgeräumt wurde
		bool engineClean;

		// Der Game-Timer
		GameTimer *timer;
	};

}

#endif
