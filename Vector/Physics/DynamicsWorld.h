/** 
 * Project Vector
 * Dynamikwelt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _DYNAMICSWORLD_H
#define _DYNAMICSWORLD_H

#include "global.h"

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine verwaltet
	class DynamicsWorld
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		DynamicsWorld(void) {}

		//! Destruktor
		virtual ~DynamicsWorld(void);
		
	};

}}

#endif
