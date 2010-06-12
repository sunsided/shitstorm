/** 
 * Project Vector
 * Manager für Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _OBJECTCLASSGROUPMANAGERBASE_H
#define _OBJECTCLASSGROUPMANAGERBASE_H

#include "global.h"
#include "ObjectClass.h"
#include "ObjectClassGroup.h"

namespace pv {
namespace world {

	//! Element mit Namen
	class ObjectClassManagerBase
	{
	protected:

		//! Konstruktor
		ObjectClassManagerBase() {}

	public:

		//! Destruktor
		virtual ~ObjectClassManagerBase(void) {}

	protected:

		//! Setzt die Gruppen-ID
		void setGroupId(ObjectClassGroupBase* group, irr::u32 id) {
			group->setGroupId(id);
		}

		//! Setzt die Klassen-ID
		void setClassId(ObjectClass* cls, irr::u32 id) {
			cls->setClassId(id);
		}

	};

	
}}


#endif
