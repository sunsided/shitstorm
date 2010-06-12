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
#include "Scripting.h"
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
		
		//! Führt ein Script (inline) aus
		/* @code vm->executeScriptCode(L"print(\"1+3=\"+ (1+3) +\"!\");"); @endcode
		 */
		void executeScriptCode(const irr::core::stringw script) const;

		//! Führt ein Script (Datei) aus
		/* @code vm->executeScriptFile(L"/path/to/file/script.nut"); @endcode
		 */
		void executeScriptFile(const irr::core::stringw filename) const;

		//! Ruft ein Event auf, falls es existiert
		/* @returns true, wenn das Event aufgerufen wurde, ansonsten false. */
		bool callEventIfExists(const irr::core::stringw eventName) const;
		
		//! Bezieht die VM
		static inline HSQUIRRELVM& getVM() { return get()->vm; }

		//! Bezieht die VM
		static inline HSQUIRRELVM* getVMPtr() { return &(get()->vm); }

		//! Setzt eine Konstante
		void setRootValue(irr::core::stringw name, int value);

		//! Setzt eine Konstante
		void setRootValue(irr::core::stringw name, float value);

		//! Setzt eine Konstante
		void setRootValue(irr::core::stringw name, irr::core::stringw value);

	private:

		//! Initialisiert die Engine.
		/** Muss als erste Funktion aufgerufen werden.
		 * @param stackSize		Die initiale Größe des Stacks
		 */
		void initialize(irr::u32 stackSize = 1024);

		//! Deinitialisiert die VM
		void terminate();

		//! Bindet die Klassen
		static void bindElements(HSQUIRRELVM& vm);

	private:

		//! Gibt an, ob die VM initialisiert wurde
		bool initialized;

		//! Die VM
		HSQUIRRELVM vm;
	};

}}

#endif
