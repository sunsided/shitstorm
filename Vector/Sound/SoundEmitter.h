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

	public:
		//! Erzeugt eine neue Instanz des Objektes
		SoundEmitter(void);

		// Destruktor
		virtual ~SoundEmitter(void);

		//! Weist diesem Emitter einen Puffer zu
		void attachBuffer(SingleSoundBuffer* buffer);

		//! Entfernt den verknüpften Puffer
		void detachBuffer();

		//! Spielt den Puffer ab
		void play();

		//! Unterbricht das Abspielen
		void pause();

		//! Hält das Abspielen an
		void stop();

		//! Emittelt, ob dieser Emitter gerade spielt
		bool isPlaying();

		//! Ermittelt die ID dieses Emitters
		inline irr::u32 getEmitterId() const { return soundEmitterId; }

		//! Ermittelt das Elterndevice
		inline SoundDevice* getParentDevice() const { return parentDevice; }

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
