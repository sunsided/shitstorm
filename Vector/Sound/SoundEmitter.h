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
#include "SoundSpaceObject.h"
#include "SingleSoundBuffer.h"
#include "SoundBuffer.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der Klassen
	class SoundDevice;

	//! Sound Emitter (OpenAL Source)
	class SoundEmitter : public SoundSpaceObject
	{
		friend class SoundDevice;

	protected:

		//! Erzeugt eine neue Instanz des Objektes
		SoundEmitter(void);

	public:

		// Destruktor
		virtual ~SoundEmitter(void);

		//! Weist diesem Emitter einen Puffer zu
		void attachBuffer(SingleSoundBuffer* buffer);

		//! Entfernt den verknüpften Puffer
		void detachBuffer();

		//! Spielt den Puffer ab
		void play() const;

		//! Unterbricht das Abspielen
		void pause() const;

		//! Hält das Abspielen an
		void stop() const;

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

		//! Ermittelt das Elterndevice
		inline SoundDevice* getParentDevice() const { return parentDevice; }

		//! Emittelt, ob dieser Emitter in einer Schleife spielt
		bool isLooping() const;

		//! Setzt, ob dieser Emitter in einer Schleife spielt
		void setLooping(bool looping = true) const;

		//! Setzt die Verstärkung
		void setGain(irr::f32 gain);

		//! Ermittelt die Verstärkung
		irr::f32 getGain();

		//! Setzt die Position
		void setPosition(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Ermittelt die Position
		void getPosition(irr::f32& x, irr::f32& y, irr::f32& z);

		//! Setzt die Geschwindigkeit
		void setVelocity(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Ermittelt die Geschwindigkeit
		void getVelocity(irr::f32& x, irr::f32& y, irr::f32& z);

		//! Setzt die Richtung zurück
		void resetOrientation();

		//! Setzt die Richtung
		void setOrientation(irr::core::vector3df& direction);

		//! Setzt die Richtung
		void setOrientation(irr::f32 x, irr::f32 y, irr::f32 z);

		//! Ermittelt die Geschwindigkeit
		void getOrientation(irr::f32& x, irr::f32& y, irr::f32& z);

	private:

		//! Erzeugt den Kontext
		void createEmitter();

		//! Vernichtet den Kontext
		void destroyEmitter();

		//! Setzt die Kontext-ID
		inline void setEmitterId(SoundDevice* parent, irr::u32 id) { soundEmitterId = id; parentDevice = parent; }

	private:

		//! Eltern-Device
		SoundDevice* parentDevice;

		//! ID des Emitters
		irr::u32 soundEmitterId;

		//! Der angehängte Puffer
		SoundBuffer* attachedBuffer;

		//! Die OpenAL-ID der Quelle
		ALuint sourceId;

		// Gibt an, ob die Quelle erstellt wurde
		bool created;
	};

}}

#endif
