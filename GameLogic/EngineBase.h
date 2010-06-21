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
#include "Physics/PhysicsManager.h"
#include "World/WorldManager.h"
#include "Sound/SoundDeviceManager.h"
#include "Sound/RoamingSoundListener.h"
#include "Scripting/ScriptingVM.h"

#define PHYSICS_MAX_SUBSTEPS_DEFAULT	(10)
#define PHYSICS_FIXED_TIMESTEP_DEFAULT	(1.0f/60.0f)

namespace pv {

	//! Basisklasse der Spiele-Engine.
	class EngineBase 
	{
	protected:

		//! Erzeugt eine neue Instanz der EngineBase-Klasse.
		EngineBase(void);

	public:

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

		//! Ermittelt, ob das Spiel läuft
		inline bool isRunning() const { return _isRunning; }

	private:

		//! Schließt die Engine
		void close();

	protected:

		//! Bindet die Engine an die Scripting-VM
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual void OnBindToScriptingVM() = 0;

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual EngineStatusCode OnSetupEngine() = 0;

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual void OnTeardownEngine() = 0;

		//! Initialisiert die Szene
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		virtual void OnSetupScene() {};

		//! Initialisiert die Spielschleife
		/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
		 * ob die Hauptschleife durchlaufen werden soll.
		 * @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
		 */
		inline virtual bool OnPreSceneLoop(irr::f32 elapsedTime) { return true; }

		//! Implementierung der Haupt-Spielschleife
		virtual void OnSceneLoop(irr::f32 elapsedTime) = 0;

		//! Hält das Spiel an
		void pause();

		//! Setzt das Spiel fort
		void unpause();

		//! Ermittelt, ob das Spiel angehalten wurde
		inline bool isPaused() const { return paused; }

		//! Handler für das Pause-Ereignis
		virtual void OnPause() = 0;

		//! Handler für das Unpause-Ereignis
		virtual void OnUnpause() = 0;

		//! Ermittelt, ob das Spiel in den Pause-Modus wechseln sollte.
		/** Das Standardverhalten richtet sich nach dem Fokus des Hauptfensters.
		 *  Hat das Fenster den Fokus verloren (und wurde noch keine Pause aktiviert),
		 *  so gibt diese Funktion den Wert true zurück.
		 * @returns true, wenn das Spiel in den Pause-Modus wechseln soll
		 */
		virtual bool shouldPause() const { return !(paused || irrlichtDevice->isWindowActive()); }

		//! Ermittelt, ob das Spiel den Pause-Modus verlassen sollte
		/** Das Standardverhalten richtet sich nach dem Fokus des Hauptfensters.
		 *  Hat das Fenster den Fokus bekommen (und ist der Pausenmodus aktiviert),
		 *  so gibt diese Funktion den Wert true zurück.
		 * @returns true, wenn das Spiel in den Pausen-Modus verlassen soll
		 */
		virtual bool shouldUnpause() const { return paused && irrlichtDevice->isWindowActive(); }

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

		//! Bezieht den Physikmanager
		inline physics::PhysicsManager* getPhysics() const { return physicsManagement; }

		//! Bezieht den Weltmanager
		inline world::WorldManager* getWorld() const { return worldManagement; }

		//! Bezieht den Timer
		inline GameTimer* getTimer() const { return timer; }

		//! Setzt den Audio-State auf Standardwerte
		void setDefaultAudioState() const;

		//! Erzeugt einen neuen Szenenmanager
		inline irr::scene::ISceneManager* createAuxiliarySceneManager() const { return sceneManager->createNewSceneManager(); }

		//! Erzeugt einen neuen Szenenmanager
		inline irr::scene::ISceneManager* createAuxiliarySceneManager(irr::scene::ISceneManager* smgr, bool clone = false) const { 
			ASSERT(smgr);
			return smgr->createNewSceneManager(clone); 
		}

		//! Setzt die Farbe, mit der die Szene geleert wird
		inline void setClearColor(const irr::video::SColor &color) {
			sceneClearColor = color;
		}

		//! Setzt die Farbe, mit der die Szene geleert wird
		const inline irr::video::SColor &getClearColor() const { return sceneClearColor; }

		//! Beginnt die Szene
		inline void beginScene(bool zBuffer = true) { 
			videoDriver->beginScene(true, zBuffer, sceneClearColor);
			sceneStarted = true;
		}

		//! Beendet die Szene
		inline void endScene() {
			if (sceneStarted) videoDriver->endScene();
			sceneStarted = false;
		}

		//! Rendert die Szene
		inline void renderScene() {
			ASSERT(sceneStarted);
			sceneManager->drawAll(); 
		}

		//! Rendert die Szene
		inline void renderScene(scene::ISceneManager* smgr) {
			ASSERT(smgr);
			smgr->drawAll(); 
		}

		//! Rendert die Szene
		inline void renderGui() { 
			ASSERT(sceneStarted);
			guiEnvironment->drawAll(); 
		}

		//! Zeichnet einen Würfel zur Orientierung um die gewählte Kamera
		/**
		 * @param camera Die aktive Kamera
		 */
		void drawCameraOrientationCage(irr::scene::ICameraSceneNode *camera = NULL);

		//! Liefert ein generisches, unbeleuchtetes Material
		const irr::video::SMaterial &getUnlitMaterial() const { return unlitMaterial; }

		//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
		/** Aktualisiert alle registrierten Dynamikwelten.
		* @param deltaTime		Die vergangene Zeit in Sekunden
		* @param maxSubsteps	Die maximale Anzahl Unterschritte
		* @param fixedTimeStep	Der fixe Zeitschritt; Bullet-Standard ist 1/60
		*/
		inline void updatePhysics(float deltaTime, short unsigned int maxSubsteps, float fixedTimeStep) const {
			ASSERT(physicsManagement);
			physicsManagement->update(deltaTime * physicsUpdateFactor, maxSubsteps, fixedTimeStep);
		}

		//! Steppt mit einem gegebenen Zeitintervall durch die Simulation
		/** Aktualisiert alle registrierten Dynamikwelten.
		* @param deltaTime		Die vergangene Zeit in Sekunden
		*/
		inline void updatePhysics(float deltaTime) const {
			ASSERT(physicsManagement);
			physicsManagement->update(deltaTime * physicsUpdateFactor, physicsMaxSubsteps, physicsFixedTimestep);
		}

		//! Bezieht den Audiokontext
		inline sound::SoundDeviceManager* getSoundDeviceManager() const { return audioManager; }

		//! Bezieht den Audiokontext
		inline sound::SoundContext* getSoundContext() const { return audioContext; }

		//! Bezieht den Audiokontext
		inline sound::SoundDevice* getSoundDevice() const { return audioDevice; }

		//! Bezieht den Audiolistener
		inline sound::RoamingSoundListener* getSoundListener() const { return audioListener; }

		//! Bezieht den Audio-State
		inline sound::SoundState* getSoundState() const { return audioState; }

		//! Bezieht die Scripting-VM
		inline scripting::ScriptingVM* getScriptVM() const { return vm; }

		//! Ermittelt, ob Physik-Debugging aktiviert ist
		inline bool physicsDebuggingEnabled() const { return enablePhysicsDebugging; }

		//! Gibt an, ob Physik-Debugging aktiviert ist
		inline void setPhysicsDebuggingEnabled(const bool& enabled) { enablePhysicsDebugging = enabled; }

		//! Maximale Anzahl der Teilschritte in Bullet
		inline irr::u32 getPhysicsMaxSubsteps() const { return physicsMaxSubsteps; }

		//! Maximale Anzahl der Teilschritte in Bullet
		inline void setPhysicsMaxSubsteps(irr::u32 steps) { physicsMaxSubsteps = steps; }

		//! Größe des fixen Timesteps in Bullet
		inline irr::f32 getPhysicsFixedTimestep() const { return physicsFixedTimestep; }

		//! Größe des fixen Timesteps in Bullet
		inline void setPhysicsFixedTimestep(irr::f32 step) { physicsFixedTimestep = step; }

		//! Größe des fixen Timesteps in Bullet
		inline irr::f32 getPhysicsUpdateFactor() const { return physicsUpdateFactor; }

		//! Größe des fixen Timesteps in Bullet
		inline void setPhysicsUpdateFactor(irr::f32 factor) { physicsUpdateFactor = factor; }

		//! Führt ein Yield auf dem Device aus
		inline void yieldDevice() { if (irrlichtDevice) irrlichtDevice->yield(); }

		//! Führt ein Yield auf dem Device aus
		inline void yieldAndSleepDevice(irr::u32 time) { if (!irrlichtDevice) return; irrlichtDevice->yield(); irrlichtDevice->sleep(time); }

	private:

		//! Ermittelt den Videotreiber
		/**
		 * @param driverHint	Der vom Benutzer gewählte Treiber
		 * @returns				Der von der Irrlicht-Engine zu verwendende Treiber
		 */
		irr::video::E_DRIVER_TYPE selectVideoDriver(VideoDriver driverHint) const;

		//! Initialisiert die Standardmaterialien
		void initializeBasicMaterials();

		//! Bindet die Klasse an die Scripting-VM
		void bindToScriptingVM();

		//! Markiert das Spiel aus laufend
		inline void setRunning(bool running) { _isRunning = running; }

	private:

		//! Das Irrlicht-Device
		irr::IrrlichtDevice* irrlichtDevice;

		//! Der Videotreiber
		irr::video::IVideoDriver* videoDriver;
		
		//! Der Szenenmanager
		irr::scene::ISceneManager* sceneManager;

		//! Die GUI
		irr::gui::IGUIEnvironment* guiEnvironment;

		//! Die Physik-Managementklasse
		physics::PhysicsManager* physicsManagement;

		//! Die Weltobjekt-Managementklasse
		world::WorldManager* worldManagement;

		//! Gibt an, ob die Engine aufgeräumt wurde
		bool engineClean;

		//! Der Game-Timer
		GameTimer *timer;

		//! Gibt an, ob das Spiel angehalten wurde
		volatile bool paused;

		//! Gibt an, ob die Szene gestartet wurde
		bool sceneStarted;

		//! Die Farbe, mit der die Szene gefüllt wird
		irr::video::SColor sceneClearColor;

		//! Ein nicht beleuchtetes Standardmaterial
		irr::video::SMaterial unlitMaterial;

		//! Der Sound Device Manager
		sound::SoundDeviceManager *audioManager;

		//! Das Haupt-Audiodevice
		sound::SoundDevice *audioDevice;

		//! Der Audiokontext
		sound::SoundContext *audioContext;

		//! Der Audio-Listener
		sound::RoamingSoundListener *audioListener;

		//! Der Sound-State
		sound::SoundState *audioState;

		//! Scripting-VM
		scripting::ScriptingVM *vm;

		//! Ermittelt, ob die Hauptschleife läuft
		volatile bool _isRunning;

		//! Ermittelt, ob Physik-Debugging aktiviert sein soll
		bool enablePhysicsDebugging;

		//! Maximale Anzahl der Teilschritte in Bullet
		irr::u32 physicsMaxSubsteps;

		//! Maximale Anzahl der Teilschritte in Bullet
		irr::f32 physicsFixedTimestep;

		//! Physik-Updatefaktor
		irr::f32 physicsUpdateFactor;
	};

}

#endif
