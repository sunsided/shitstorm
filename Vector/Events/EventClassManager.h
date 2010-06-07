/** 
 * Project Vector
 * Manager für Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTCLASSGROUPMANAGER_H
#define _EVENTCLASSGROUPMANAGER_H

#include "global.h"
#include "Utility/Singleton.h"
#include "Utility/Manager.h"
#include "EventClass.h"
#include "EventClassGroup.h"

namespace pv {
namespace events {

	//! Element mit Namen
	class EventClassManager : public utility::Singleton<EventClassManager>
	{
		friend class utility::Singleton<EventClassManager>;

	private:

		//! Konstruktor
		inline EventClassManager() : groups(true) {}

	public:

		//! Destruktor
		virtual ~EventClassManager(void) {}

		//! Ermittelt die Anzahl der registrierten Gruppen
		inline irr::u32 getGroupCount() { return groups.count(); }

		//! Ermittelt die Anzahl der registrierten Gruppen
		inline irr::u32 getClassCount() { return groups.count(); }

		//! Erzeugt eine Gruppe
		EventClassGroup* createGroup();

		//! Erzeugt eine Klasse
		EventClass* createClass();

		//! Erzeugt eine Klasse
		EventClass* createClass(irr::core::stringw& description);

		//! Bezieht eine Gruppe
		EventClassGroup* getGroup(irr::u32 groupId) { return groups[groupId]; }

		//! Bezieht eine Gruppe
		EventClass* getClass(irr::u32 classId) { return classes[classId]; }

	private:

		//! Manager der Gruppen
		utility::Manager<EventClassGroup> groups;

		//! Manager der Klassen
		utility::Manager<EventClass> classes;
	};

	//! Bezieht eine Event-Klasse anhand ihrer ID
	EventClass* eventGetClassFromId(irr::u32 eventClassId) {
		return EventClassManager::get()->getClass(eventClassId);
	}

	//! Bezieht eine Event-Klasse anhand ihrer ID
	bool eventIsClassInGroup(irr::u32 eventClassId, irr::u32 classGroupId) {
		return EventClassManager::get()->getGroup(classGroupId)->containsClass(eventClassId);
	}
	
}}


#endif
