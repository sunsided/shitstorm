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

namespace pv {
namespace sound {

//! Sound Emitter (OpenAL Source)
class SoundEmitter : public SoundSpaceObject
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundEmitter(void);

	// Destruktor
	virtual ~SoundEmitter(void);
};

}}

#endif
