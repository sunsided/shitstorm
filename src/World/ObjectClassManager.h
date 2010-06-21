/** 
 * Project Vector
 * Manager f�r Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _OBJECTCLASSGROUPMANAGER_H
#define _OBJECTCLASSGROUPMANAGER_H

#include "global.h"
#include "Utility/Singleton.h"
#include "Utility/Manager.h"
#include "ObjectClassManagerBase.h"
#include "ObjectClass.h"
#include "ObjectClassGroup.h"

namespace pv {
namespace world {

	//! Element mit Namen
	template <class TObjectClass, class TObjectClassGroup>
	class ObjectClassManager : public utility::Singleton<ObjectClassManager<TObjectClass, TObjectClassGroup> >, public ObjectClassManagerBase
	{
		friend class utility::Singleton<ObjectClassManager<TObjectClass, TObjectClassGroup> >;

	private:

		//! Konstruktor
		inline ObjectClassManager() : groups(true), ObjectClassManagerBase() {}

	public:

		//! Destruktor
		virtual ~ObjectClassManager(void) {}

		//! Ermittelt die Anzahl der registrierten Gruppen
		inline irr::u32 getGroupCount() { return groups.count(); }

		//! Ermittelt die Anzahl der registrierten Gruppen
		inline irr::u32 getClassCount() { return groups.count(); }

		//! H�ngt ein Weltobjekt ein
		TObjectClassGroup* createGroup() {
			TObjectClassGroup* group = new TObjectClassGroup();
			irr::s32 id = groups.add(group);
			setGroupId(group, id);
			return group;
		}

		//! Erzeugt eine Klasse
		TObjectClass* createClass() {
			TObjectClass* cls = new TObjectClass();
			irr::s32 id = classes.add(cls);
			setClassId(cls, id);
			return cls;
		}

		//! Erzeugt eine Klasse
		TObjectClass* createClass(irr::core::stringw& description) {
			TObjectClass* cls = new TObjectClass(description);
			irr::s32 id = classes.add(cls);
			setClassId(cls, id);
			return cls;
		}

		//! Bezieht eine Gruppe
		TObjectClassGroup* getGroup(irr::u32 groupId) { return groups[groupId]; }

		//! Bezieht eine Gruppe
		TObjectClass* getClass(irr::u32 classId) { return classes[classId]; }

	private:

		//! Manager der Gruppen
		utility::Manager<TObjectClassGroup> groups;

		//! Manager der Klassen
		utility::Manager<TObjectClass> classes;
	};

}}


#endif
