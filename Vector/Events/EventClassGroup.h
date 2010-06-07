/** 
 * Project Vector
 * Gruppe von Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTCLASSGROUP_H
#define _EVENTCLASSGROUP_H

#include "global.h"
#include "Utility/SetManager.h"
#include "EventTriggeringObject.h"

namespace pv {
namespace events {

	//! Element mit Namen
	class EventClassGroup
	{
		friend class EventClassGroupManager;

	protected:

		//! Konstruktor
		inline EventClassGroup() {}

	public:

		//! Destruktor
		virtual ~EventClassGroup(void) { classIds.clear(); }

		//! Prüft, ob die Gruppe eine Klasse enthält
		inline bool containsClass(irr::u32 classId) { return classIds.contains(classId); }

		//! Prüft, ob die Gruppe eine Klasse enthält
		inline bool containsClass(const EventTriggeringObject* object) const { ASSERT(object); return classIds.contains(object->getEventClass()); }

		//! Fügt der Gruppe eine Klasse hinzu
		inline void addClass(irr::u32 classId) { return classIds.add(classId); }

		//! Fügt der Gruppe eine Klasse hinzu
		inline void removeClass(irr::u32 classId) { return classIds.remove(classId); }

		//! Wandelt die Gruppe in einen Integer (ihre ID) um
		inline operator irr::u32() const { return groupId; }

	private:

		//! Setzt die Gruppen-ID
		inline void setGroupId(irr::u32 id) { groupId = id; }

	private:

		//! Die Gruppen-ID
		irr::u32 groupId;

		//! Die Klassen-IDs
		utility::SetManager<irr::u32> classIds;
	};

}}

#endif
