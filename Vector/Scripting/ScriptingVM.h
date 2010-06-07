/** 
 * Project Vector
 * Scripting-VM
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SCRIPTINGVM_H
#define _SCRIPTINGVM_H

#include "global.h"
#include "Utility/Singleton.h"

namespace pv {
namespace scripting {

	//! Virtuelle Maschine für das Scripting
	class ScriptingVM : public utility::Singleton<ScriptingVM>
	{
		friend class utility::Singleton<ScriptingVM>;

	private:

		//! Erzeugt eine neue Instanz der VM
		ScriptingVM();

	public:

		//! Destruktor
		virtual ~ScriptingVM();
		
	private:

		//! Initialisiert die Engine.
		/** Muss als erste Funktion aufgerufen werden.
		 * @param stackSize		Die initiale Größe des Stacks
		 */
		void initialize(irr::u32 stackSize = 1024);

		//! Deinitialisiert die VM
		void terminate();

		//! Gibt an, ob die VM initialisiert wurde
		bool initialized;
	};

}}

#endif
