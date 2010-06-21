/** 
 * Project Vector
 * Objekt mit Namen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _NAMEDOBJECT_H
#define _NAMEDOBJECT_H

#include "global.h"

namespace pv {
namespace world {

	//! Element mit Namen
	class NamedObject
	{
	protected:

		//! Konstruktor
		inline NamedObject(irr::core::stringc name = Unnamed) : _elementName(name) {}

	public:

		//! Destruktor
		virtual ~NamedObject(void) {}

		//! Liefert den Namen des Elementes
		inline irr::core::stringc getName() const { return _elementName; }

		//! Setzt den Namen des Elementes
		inline void setName(irr::core::stringc name) { _elementName = name; }

	public:

		//! Defaultwert für unbenamte Objekte
		static const irr::core::stringc Unnamed;

	private:

		//! Der Name des Elementes
		irr::core::stringc _elementName;
	};

	// Initialisiert den Defaultwert
	const irr::core::stringc NamedObject::Unnamed = "(unnamed)";

}}

#endif
