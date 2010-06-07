/** 
 * Project Vector
 * Objekt, das Events auslösen kann
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTTRIGGERINGOBJECT_H
#define _EVENTTRIGGERINGOBJECT_H

#include "global.h"

namespace pv {
namespace events {

	//! Element mit Namen
	class EventTriggeringObject
	{
	protected:

		//! Konstruktor
		inline EventTriggeringObject(irr::u32 eventClass = 0) : triggerClass(eventClass) {}

	public:

		//! Destruktor
		virtual ~EventTriggeringObject(void) {}

		//! Liefert die Klasse des Elementes
		inline irr::u32 getEventClass() const { return triggerClass; }

		//! Setzt die Klasse des Elementes
		inline void setEventClass(irr::u32 eventClass) { triggerClass = eventClass; }

		//! Testet, ob das Objekt einer bestimmten Event-Klasse angehört
		inline bool isEventClass(irr::u32 testClass) const { return triggerClass == testClass; }
		
		//! Testet, ob das Objekt einer bestimmten Event-Klasse angehört
		inline bool isSameEventClass(const EventTriggeringObject &otherObject) const { return triggerClass == otherObject.triggerClass; }

		//! Testet, ob das Objekt einer bestimmten Event-Klasse angehört
		inline bool isSameEventClass(const EventTriggeringObject *otherObject) const { ASSERT(otherObject); return triggerClass == otherObject->triggerClass; }

	private:

		//! Die Event-Klasse des Objektes
		irr::u32 triggerClass;
	};

}}

#endif
