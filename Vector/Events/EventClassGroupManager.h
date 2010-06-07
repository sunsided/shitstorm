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
#include "EventClassGroup.h"

namespace pv {
namespace events {

	//! Element mit Namen
	class EventClassGroupManager : public utility::Singleton<EventClassGroupManager>
	{
		friend class utility::Singleton<EventClassGroupManager>;

	private:

		//! Konstruktor
		inline EventClassGroupManager() : groups(true) {}

	public:

		//! Destruktor
		virtual ~EventClassGroupManager(void) {}

		//! Ermittelt die Anzahl der registrierten Gruppen
		inline irr::u32 getGroupCount() { return groups.count(); }

		//! Erzeugt eine Gruppe
		EventClassGroup* createGroup();

		//! Erzeugt eine Gruppe
		EventClassGroup* getGroup(irr::u32 groupId) { return groups[groupId]; }

	private:

		//! Manager der Gruppen
		utility::Manager<EventClassGroup> groups;
	};

}}

#endif
