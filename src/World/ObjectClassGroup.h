/** 
 * Project Vector
 * Gruppe von Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _OBJECTCLASSGROUP_H
#define _OBJECTCLASSGROUP_H

#include "global.h"
#include "Utility/SetManager.h"
#include "ObjectClass.h"

namespace pv {
namespace world {

	//! Element mit Namen
	class ObjectClassGroupBase
	{
		friend class ObjectClassManagerBase;

	protected:

		//! Konstruktor
		inline ObjectClassGroupBase() {}

	public:

		//! Destruktor
		virtual ~ObjectClassGroupBase(void) {}

		//! Wandelt die Gruppe in einen Integer (ihre ID) um
		inline operator irr::u32() const { return groupId; }

		//! Wandelt die Gruppe in einen Integer (ihre ID) um
		inline irr::u32 getGroupId() const { return groupId; }

	protected:

		//! Setzt die Gruppen-ID
		inline void setGroupId(irr::u32 id) { groupId = id; }

	private:

		//! Die Gruppen-ID
		irr::u32 groupId;
	};

	//! Element mit Namen
	template <class TObjectClass>
	class ObjectClassGroup : public ObjectClassGroupBase
	{
		friend class ObjectClassManagerBase;

	public:

		//! Konstruktor
		inline ObjectClassGroup() {}

	public:

		//! Destruktor
		virtual ~ObjectClassGroup(void) { classes.clear(); }
		
		//! Prüft, ob die Gruppe eine Klasse enthält
		inline bool containsClass(TObjectClass cls) { return classes.contains(cls); }

		//! Fügt der Gruppe eine Klasse hinzu
		inline void addClass(TObjectClass* classId) { return classes.add(classId); }
		
		//! Entfernt eine Klasse aus der Gruppe
		inline void removeClass(TObjectClass* cls) { return classes.remove(cls); }

	private:

		//! Die Klassen-IDs
		utility::SetManager<TObjectClass> classes;
	};

}}

#endif
