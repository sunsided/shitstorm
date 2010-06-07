/** 
 * Project Vector
 * Event Class-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTCLASSBINDINGS_H
#define _EVENTCLASSBINDINGS_H

#include "global.h"
#include "Scripting/Scripting.h"
#include "Events/EventClass.h"

using namespace pv::events;

/*
DECLARE_INSTANCE_TYPE_NAME(pv::events::EventClass, EventClass)

//! Bindet die EventClass-Klasse
void scriptingBindEventClass() {
    SqPlus::SQClassDef<EventClass>(_T("EventClass")).
        func(&EventClass::getDescription,_T("getDescription")).
        func(&EventClass::getId,_T("getId")).
        func(&EventClass::setDescription,_T("setDescription"));
}
*/

#endif
