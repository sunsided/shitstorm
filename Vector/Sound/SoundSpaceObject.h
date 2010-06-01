/** 
 * Project Vector
 * Soundobjekt im 3D-Raum
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDSPACEOBJECT_H
#define _SOUNDSPACEOBJECT_H

#include "global.h"

namespace pv {
namespace sound {

//! Soundobjekt im 3D-Raum
class SoundSpaceObject
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	SoundSpaceObject(void);

	// Destruktor
	virtual ~SoundSpaceObject(void);
};

}}

#endif
