/** 
 * Project Vector
 * Gruppe von Event-Klassen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTCLASS_H
#define _EVENTCLASS_H

#include "global.h"

namespace pv {
namespace events {

	//! Element mit Namen
	class EventClass
	{
		friend class EventClassManager;

	protected:

		//! Konstruktor
		inline EventClass(irr::core::stringw text = L"") : description(text), classId(0) {}
		
	public:

		//! Destruktor
		virtual ~EventClass(void) {}

		//! Ermittelt die Klassen-ID
		inline irr::u32 getId() const { return classId; }

		//! Setzt die Beschreibung
		inline void setDescription(irr::core::stringw text) { description = text; }

		//! Ermittelt die Beschreibung
		inline irr::core::stringw getDescription() const { return description; }

		//! Wandelt die Gruppe in einen Integer (ihre ID) um
		inline operator irr::u32() const { return classId; }

		//! Wandelt die Gruppe in einen String (die Beschreibung) um
		inline operator irr::core::stringw() const { return description; }

	private:

		//! Setzt die Gruppen-ID
		inline void setClassId(irr::u32 id) { classId = id; }

	private:

		//! Die Gruppen-ID
		irr::u32 classId;

		//! Die Beschreibung der Gruppe
		irr::core::stringw description;
	};

}}

#endif
