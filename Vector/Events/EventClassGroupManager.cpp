/** 
 * Project Vector
 * Manager für Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "EventClassGroupManager.h"

namespace pv {
namespace events {

	//! Hängt ein Weltobjekt ein
	EventClassGroup* EventClassGroupManager::createGroup() {
		EventClassGroup* group = new EventClassGroup();
		irr::s32 id = groups.add(group);
		group->setGroupId(id);
		return group;
	}

}}