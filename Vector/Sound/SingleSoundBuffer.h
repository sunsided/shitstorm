/** 
 * Project Vector
 * Soundpuffer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SINGLESOUNDBUFFER_H
#define _SINGLESOUNDBUFFER_H

#include "global.h"
#include "SoundBuffer.h"

namespace pv {
namespace sound {

	// Vorwärtsdeklaration der Klassen
	class SoundDevice;

	//! Soundpuffer
	class SingleSoundBuffer : SoundBuffer
	{
		friend class SoundDevice;

	protected:

		//! Erzeugt eine neue Instanz des Objektes
		SingleSoundBuffer(SoundDevice* device);

	public:

		// Destruktor
		virtual ~SingleSoundBuffer(void);

	};

}}

#endif
