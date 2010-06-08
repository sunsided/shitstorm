/** 
 * Project Vector
 * Helfer für Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _BINDINGS_H
#define _BINDINGS_H

#include "global.h"
#include "Scripting.h"

namespace pv {
namespace scripting {

	//! Bindet die Klassen an das Scripting-System
	void bindElements(HSQUIRRELVM& vm);

}}

#endif
