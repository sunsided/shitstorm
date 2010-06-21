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
#include "World/WorldObjectFactory.h"
#include "Sound/OggVorbisAudioSource.h"

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

		//! Bindet die Engine an die Scripting-VM
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		void OnBindToScriptingVM();

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		EngineStatusCode OnSetupEngine();

		//! Initialisiert die Engine
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		void OnTeardownEngine();

		//! Initialisiert die Szene
		/** Diese Funktion dient zur Initialisierung von überladenen Klassen */
		void OnSetupScene();

		//! Initialisiert die Spielschleife
		/** Wird zu Beginn jedes Schleifendurchgangs aufgerufen und ermittelt,
		 * ob die Hauptschleife durchlaufen werden soll.
		 * @returns	true, wenn die Hauptschleife aufgerufen werden soll, sonst false
		 */
		inline bool OnPreSceneLoop(irr::f32 elapsedTime);

		//! Implementierung der Haupt-Spielschleife
		void OnSceneLoop(irr::f32 elapsedTime);

		//! Handler für das Pause-Ereignis
		void OnPause();

		//! Handler für das Unpause-Ereignis
		void OnUnpause();

	private:

		//! Die Hauptkamera
		irr::scene::ICameraSceneNode *mainCamera;

		//! Knoten für Testzwecke
		nodes::PlaneSceneNode *testNode;

		//! Zieltextur für render to texture
		irr::video::ITexture* renderTarget;

		//! Kamera für render to texture
		irr::scene::ICameraSceneNode *renderTargetCamera;

		//! Scene Manager für renter to texture
		irr::scene::ISceneManager* renderTargetSceneManager;

		//! GUI-Element, das die Textur anzeigt
		gui::IGUIImage *image;

		//! Einfacher Soundemitter
		sound::SoundEmitter *simpleEmitter;

		//! Einfacher Soundemitter
		sound::SoundEmitter *blipEmitter;

		//! Einfacher Soundemitter
		sound::SoundEmitter *emitterSinus220;

		//! Einfacher Soundemitter
		sound::SoundEmitter *emitterSinus440;

		//! Einfacher Soundpuffer
		sound::SingleSoundBuffer *bufferSinus220;

		//! Einfacher Soundpuffer
		sound::SingleSoundBuffer *bufferSinus440;

		//! Einfacher Soundpuffer
		sound::SingleSoundBuffer *singleBuffer;

		//! Streaming-Soundpuffer
		sound::StreamingSoundBuffer *streamingBuffer;

		//! Streaming-Audioquelle
		sound::OggVorbisAudioSource *streamingAudioSource;
	};

}

#endif