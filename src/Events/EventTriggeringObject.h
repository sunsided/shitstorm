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
#include "EventClasses.h"

namespace pv {
namespace events {

	//! Element mit Namen
	class EventTriggeringObject
	{
	protected:

		//! Konstruktor
		inline EventTriggeringObject(EventClass* eventClass = 0) : triggerClass(eventClass) {}

	public:

		//! Destruktor
		virtual ~EventTriggeringObject(void) {}

		//! Liefert die Klasse des Elementes
		inline EventClass* getObjectClass() const { return triggerClass; }

		//! Setzt die Klasse des Elementes
		inline void setObjectClass(EventClass* eventClass) { triggerClass = eventClass; }

		//! Testet, ob das Objekt einer bestimmten Event-Klasse angehört
		inline bool isObjectClass(const EventClass* testClass) const { return triggerClass == testClass; }
		
		//! Testet, ob das Objekt einer bestimmten Event-Klasse angehört
		inline bool isSameObjectClass(const EventTriggeringObject &otherObject) const { return triggerClass == otherObject.triggerClass; }

		//! Testet, ob das Objekt einer bestimmten Event-Klasse angehört
		inline bool isSameObjectClass(const EventTriggeringObject *otherObject) const { ASSERT(otherObject); return triggerClass == otherObject->triggerClass; }

	private:

		//! Die Event-Klasse des Objektes
		EventClass* triggerClass;
	};

}}

#endif
