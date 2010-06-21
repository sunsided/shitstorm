/** 
 * Project Vector
 * Soudklassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SOUNDCLASSES_H
#define _SOUNDCLASSES_H

#include "global.h"
#include "World/ObjectClass.h"
#include "World/ObjectClassGroup.h"
#include "World/ObjectClassManager.h"

namespace pv {
namespace sound {

	//! Soundklasse
	class SoundClass: public world::ObjectClass {};
	
	//! Soundklassen-Gruppe
	class SoundClassGroup: public world::ObjectClassGroup<SoundClass> {};

	//! Manager für Soundklassen
	class SoundClassManager: public world::ObjectClassManager<SoundClass, SoundClassGroup> {};
	
}}

#endif
