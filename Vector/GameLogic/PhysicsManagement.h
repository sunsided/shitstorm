/** 
 * Project Vector
 * Physikmanagement
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSMANAGEMENT_H
#define _PHYSICSMANAGEMENT_H

namespace pv {

	//! Klasse, die die Physikengine verwaltet
	class PhysicsManagement
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		PhysicsManagement(void) : initialized(false) {}

		//! Destruktor
		virtual ~PhysicsManagement(void);

		//! Initialisiert die Physikengine
		void initialize();

	private:
		
		//! Gibt an, ob die Engine initialisiert wurde
		bool initialized;
	};

}

#endif
