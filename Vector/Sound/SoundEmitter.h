/** 
 * Project Vector
 * Sound Emitter (OpenAL Source)
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDEMITTER_H
#define _SOUNDEMITTER_H

#include "global.h"
#include "PositionalAudioObject.h"
#include "SingleSoundBuffer.h"
#include "StreamingSoundBuffer.h"
#include "SoundBuffer.h"
#include "SoundEnums.h"
#include "Scripting/Bindings/SoundBindings.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der Klassen
	class SoundDevice;

	//! Sound Emitter (OpenAL Source)
	class SoundEmitter : public PositionalAudioObject
	{
		friend class SoundContext;
		friend class pv::scripting::SoundBindings;

	protected:

		//! Erzeugt eine neue Instanz des Objektes
		SoundEmitter(void);

	public:

		// Destruktor
		virtual ~SoundEmitter(void);

		//! Weist diesem Emitter einen Puffer zu
		void attachBuffer(SingleSoundBuffer* buffer);

		//! Weist diesem Emitter einen Streaming-Puffer zu
		void attachBuffer(StreamingSoundBuffer *buffer);

		//! Entfernt den verknüpften Puffer
		void detachBuffer();

		//! Spielt den Puffer ab
		void play();

		//! Unterbricht das Abspielen
		void pause();

		//! Hält das Abspielen an
		void stop();

		//! Unterbricht das Abspielen
		void pauseBySystem();

		//! Beendet die Unterbreachung
		void unpauseBySystem();

		//! Gibt an, ob das System das Abspielen erlaubt
		inline bool systemAllowsPlaying() const { return playState == SPS_CANPLAY; }

		//! Gibt an, ob das System das Abspielen verhindert
		inline bool systemPreventsPlaying() const { return playState != SPS_CANPLAY; }

		//! Spult die Quelle zurück
		void rewind() const;

		//! Emittelt, ob dieser Emitter gerade spielt
		bool isPlaying() const;

		//! Emittelt, ob dieser Emitter angehalten wurde
		bool isPaused() const;

		//! Emittelt den Status des Emitters
		ALenum getState() const;

		//! Ermittelt die ID dieses Emitters
		inline irr::u32 getEmitterId() const { return soundEmitterId; }

		//! Bezieht die OpenAL-Quelle
		inline ALuint getOpenALSource() const { return sourceId; }

		//! Ermittelt den Elternkontext
		inline SoundContext* getParentContext() const { return parentContext; }

		//! Emittelt, ob dieser Emitter in einer Schleife spielt
		bool isLooping() const;

		//! Setzt, ob dieser Emitter in einer Schleife spielt
		void setLooping(bool looping = true) const;

		//! Setzt die Verstärkung
		void setGain(irr::f32 gain) const;

		//! Ermittelt die Verstärkung
		irr::f32 getGain() const;

		//! Setzt die maximale Verstärkung
		void setMaxGain(irr::f32 gain) const;

		//! Ermittelt die maximale Verstärkung
		irr::f32 getMaxGain() const;

		//! Setzt die minimale Verstärkung
		void setMinGain(irr::f32 gain) const;

		//! Ermittelt die minimale Verstärkung
		irr::f32 getMinGain() const;

		//! Setzt die maximale Entfernung
		void setMaxDistance(irr::f32 distance) const;

		//! Ermittelt die maximale Entfernung
		irr::f32 getMaxDistance() const;

		//! Setzt die Referenzentfernung
		void setReferenceDistance(irr::f32 distance) const;

		//! Ermittelt die Referenzentfernung
		irr::f32 getReferenceDistance() const;

		//! Setzt die Position
		void setPosition(irr::f32 x, irr::f32 y, irr::f32 z) const;

		//! Ermittelt die Position
		void getPosition(irr::f32& x, irr::f32& y, irr::f32& z) const;

		//! Setzt die Geschwindigkeit
		void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z) const;

		//! Ermittelt die Geschwindigkeit
		void getVelocity(irr::f32& x, irr::f32& y, irr::f32& z) const;

		//! Setzt die Richtung zurück
		void resetOrientation() const;

		//! Setzt die Richtung
		void setOrientation(irr::core::vector3df& direction) const;

		//! Setzt die Richtung
		void setOrientation(irr::f32 x, irr::f32 y, irr::f32 z) const;

		//! Ermittelt die Richtung
		void getOrientation(irr::f32& x, irr::f32& y, irr::f32& z) const;

		//! Ermittelt die Richtung
		inline irr::core::vector3df getOrientation() const {
			irr::core::vector3df value;
			getOrientation(value.X, value.Y, value.Z);
			return value;
		}

		//! Setzt den Emitter auf ambiente Wiedergabe (AL_SOURCE_RELATIVE)
		void setRelative(bool isRelative = true) const;

		//! Setzt den Rolloff-Faktor
		void setRolloffFactor(irr::f32 factor) const;

		//! Macht die Audioquelle ambient
		inline void makeAmbient() const {
			setPosition(0, 0, 0);
			setRelative(true);
		}

		//! Ermittelt, ob dieser Emitter ein Streaming-Emitter ist
		inline bool isStreamingEmitter() const { return bufferIsStreamingBuffer; }

		//! Updated alle Streaming Audio-Puffer
		inline void updateStreamingAudio() {
			if (bufferIsStreamingBuffer) {
				ASSERT(attachedBuffer);
				static_cast<StreamingSoundBuffer*>(attachedBuffer)->updateStreamingAudio();
			}
		}

	private:

		//! Ruft das Init-Event auf, falls es existiert
		/* @returns true, wenn das Event aufgerufen wurde, ansonsten false. */
		bool callInitEventIfExists();

	private:

		//! Erzeugt den Kontext
		void createEmitter();

		//! Vernichtet den Kontext
		void destroyEmitter();

		//! Setzt die Kontext-ID
		inline void setEmitterId(SoundContext* context, irr::u32 id) { soundEmitterId = id; parentContext = context; }

		//! Spielt den Puffer ab
		void playInternal() const;

		//! Unterbricht das Abspielen
		void pauseInternal() const;

	private:

		//! Eltern-Device
		SoundContext* parentContext;

		//! ID des Emitters
		irr::u32 soundEmitterId;

		//! Der angehängte Puffer
		SoundBuffer* attachedBuffer;

		//! Gibt an, ob der verknüpfte Puffer ein Streaming-Puffer ist
		bool bufferIsStreamingBuffer;

		//! Die OpenAL-ID der Quelle
		ALuint sourceId;

		//! Gibt an, ob die Quelle erstellt wurde
		bool created;

		//! Der Abspielzustand
		SoundPlayState playState;
	};

}}

#endif
