/** 
 * Project Vector
 * Sound Listener, der den Kontext automatisch wechselt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _CONTEXTSWITCHINGSOUNDLISTENER_H
#define _CONTEXTSWITCHINGSOUNDLISTENER_H

#include "global.h"
#include "SoundListener.h"

namespace pv {
namespace sound {

//! Sound Listener, der den Kontext automatisch wechselt
class ContextSwitchingSoundListener : public SoundListener 
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	ContextSwitchingSoundListener(void);

	// Destruktor
	virtual ~ContextSwitchingSoundListener(void);
};

}}

#endif
