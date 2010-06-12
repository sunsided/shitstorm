/** 
 * Project Vector
 * Eventklassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTCLASSES_H
#define _EVENTCLASSES_H

#include "global.h"
#include "World/ObjectClass.h"
#include "World/ObjectClassGroup.h"
#include "World/ObjectClassManager.h"

namespace pv {
namespace events {

	//! Eventklasse
	class EventClass: public world::ObjectClass {};
	
	//! Eventklasse
	class EventClassGroup: public world::ObjectClassGroup<EventClass> {};

	//! Eventklasse
	class EventClassManager: public world::ObjectClassManager<EventClass, EventClassGroup> {};
	
}}

#endif
