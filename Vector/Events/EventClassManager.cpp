/** 
 * Project Vector
 * Manager für Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "EventClassManager.h"

namespace pv {
namespace events {

	//! Hängt ein Weltobjekt ein
	EventClassGroup* EventClassManager::createGroup() {
		EventClassGroup* group = new EventClassGroup();
		irr::s32 id = groups.add(group);
		group->setGroupId(id);
		return group;
	}

	//! Erzeugt eine Klasse
	EventClass* EventClassManager::createClass() {
		EventClass* cls = new EventClass();
		irr::s32 id = classes.add(cls);
		cls->setClassId(id);
		return cls;
	}

	//! Erzeugt eine Klasse
	EventClass* EventClassManager::createClass(irr::core::stringw& description) {
		EventClass* cls = new EventClass(description);
		irr::s32 id = classes.add(cls);
		cls->setClassId(id);
		return cls;
	}

}}