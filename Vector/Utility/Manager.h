/** 
 * Project Vector
 * Manager mit Listenimplementierung
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _MANAGER_H
#define _MANAGER_H

#include "global.h"
#include <map>

namespace pv {
namespace utility {

	//! Manager für beliebige Typen.
	/** Generelle Implementierung für Zeigertypen
	 */
	template<typename T>
	class Manager
	{
	public:

		//! Erzeugt eine neue Instanz des Managers
		Manager(bool deleteOnDestruction = false) : deleteOnDestruct(deleteOnDestruction), nextFreeID(0) {}
		
		//! Destruktor
		Manager<T>::~Manager(void) { clear(deleteOnDestruct); }

		//! Fügt ein Element hinzu
		/**
		 * @param element	Das hinzuzufügende Element
		 * @returns Der Index des hinzugefügten Elementes; Wird Indizierung nicht unterstützt, ist der Wert immer 0.
		 */
		irr::u32 add(T* element) {
			irr::u32 id = nextFreeID++;
			idElementTable.insert(std::pair<irr::u32, T*>(id, element));
			elementIdTable.insert(std::pair<T*, irr::u32>(element, id));
			return id;
		}

		//! Fügt ein Element hinzu
		/**
		 * @param element	Das zu entfernende Element
		 */
		void remove(T* element) {
			irr::u32 id = elementIdTable[element];
			elementIdTable.erase(element);
			idElementTable.erase(id);
		}

		//! Fügt ein Element hinzu
		/**
		 * @param element	Die ID des zu entfernenden Elementes
		 */
		void remove(irr::u32 id) {
			T* element = idElementTable[id];
			elementIdTable.erase(element);
			idElementTable.erase(id);
		}

		//! Fügt ein Element hinzu
		inline irr::u32 count() { return idElementTable.size(); }

		//! Liefert ein Element.
		/**
		 * @param index		Die gewünschte ID
		 */
		inline T* getElement(irr::u32 id) { return idElementTable[id]; }

		//! Liefert ein Element.
		/**
		 * @param element	Das gewünschte Element
		 */
		inline irr::u32 getId(T* element) { return elementIdTable[element]; }

		//! Ermittelt, ob ein Element mit der gegebenen ID registriert ist
		/*
		 * @param id	Die zu testende ID
		 * @returns		true, wenn das Element gefunden wurde, ansonsten false
		 */
		inline bool contains(irr::u32 id) const { return idElementTable.find(id) == idElementTable.end(); }

		//! Ermittelt, ob ein Element registriert ist
		/*
		 * @param id	Das zu Testende Element
		 * @returns		true, wenn das Element gefunden wurde, ansonsten false
		 */
		inline bool contains(T* element) const { return elementIdTable.find(element) == elementIdTable.end(); }
		
		//! Ermittelt, ob der Manager leer ist
		inline bool isEmpty() const { return idElementTable.empty(); }

		//! Leert den Manager
		void clear(bool deleteOnDestruct = false) {

			// Ggf. die Elemente löschen
			if (deleteOnDestruct) {
				std::map<irr::u32, T*>::const_iterator iterator;
				for (iterator = idElementTable.begin(); iterator != idElementTable.end(); ++iterator) {
					T* element = (*iterator).second;
					if (element) delete element;
				}
			}

			// Eigentlich nicht nötig, aber hey.
			idElementTable.clear();
			elementIdTable.clear();
			nextFreeID = 0;
		}

		//! Iteriert die Klasse
		/**
		 * @param iterateFunction	Die aufzurufende Funktion
		 */
		template<typename TState>
		void iterate(void(*iterateFunction)(T*, TState*), TState* userState = NULL) {
			ASSERT(iterateFunction);

			// Elemente durchlaufen
			std::map<irr::u32, T*>::const_iterator iterator;
			for (iterator = idElementTable.begin(); iterator != idElementTable.end(); ++iterator) {
				T* element = (*iterator).second;
			
				// Funktion aufrufen
				iterateFunction(element, userState);
			}
		}

		//! Indexoperator
		inline T* operator[](irr::u32 id) { return getElement(id); }

		//! Indexoperator
		inline irr::u32 operator[](T* element) { return getId(element); }

	private:

		//! Die höchste, freie ID
		volatile irr::u32 nextFreeID;

		//! Lookup von Index auf Element
		std::map<irr::u32, T*> idElementTable;

		//! Lookup von Element auf Index
		std::map<T*, irr::u32> elementIdTable;

		//! Gibt an, ob die Klasse beim Vernichten die Elemente löschen soll
		bool deleteOnDestruct;
	};

}}

#endif
