/** 
 * Project Vector
 * Basisklasse für Manager
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "Manager.h"

namespace pv {

	//! Destruktor
	template<typename T>
	Manager<T>::~Manager(void) {
		clear();
	}

	//! Leert die Klasse
	template<typename T>
	void Manager<T>::clear() {

		// Ggf. die Elemente löschen
		if (deleteOnDestruct) {
			map<irr::u32, T*>::const_iterator iterator;
			for (iterator = idElementTable.begin(); iterator != idElementTable.end(); ++iterator) {
				T* element = (*iterator).second();
				if (element) delete element;
			}
		}

		// Eigentlich nicht nötig, aber hey.
		idElementTable.clear();
		elementIdTable.clear();
		nextFreeID = 0;
	}

	//! Fügt ein Element hinzu
	/**
	* @param element	Das hinzuzufügende Element
	* @returns Der Index des hinzugefügten Elementes; Wird Indizierung nicht unterstützt, ist der Wert immer 0.
	*/
	template<typename T>
	irr::u32 Manager<T>::add(const T* element) {
		irr::u32 id = nextFreeID++;
		idElementTable.insert(std::pair<irr::u32, T*>(id, element));
		elementIdTable.insert(std::pair<T*, irr::u32>(element, id));
		return id;
	}

	//! Fügt ein Element hinzu
	/**
	* @param element	Das zu entfernende Element
	*/
	template<typename T>
	void Manager<T>::remove(const T* element) {
		irr::u32 id = elementIdTable[element];
		elementIdTable.erase(element);
		idElementTable.erase(id);
	}

	//! Fügt ein Element hinzu
	/**
	* @param element	Das zu entfernende Element
	*/
	template<typename T>
	void Manager<T>::remove(irr::u32 id) {
		T* element = idElementTable[id];
		elementIdTable.erase(element);
		idElementTable.erase(id);
	}
	
}
