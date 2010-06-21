/** 
 * Project Vector
 * Manager mit Setimplementierung
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SETMANAGER_H
#define _SETMANAGER_H

#include "global.h"
#include <set>

namespace pv {
namespace utility {

	//! Manager f�r beliebige Typen.
	/** Generelle Implementierung f�r Zeigertypen
	 */
	template<typename T>
	class SetManager
	{
	public:

		//! Erzeugt eine neue Instanz des Managers
		SetManager() {}
		
		//! Destruktor
		~SetManager(void) { clear(); }

		//! F�gt ein Element hinzu
		/**
		 * @param element	Das hinzuzuf�gende Element
		 * @returns Der Index des hinzugef�gten Elementes; Wird Indizierung nicht unterst�tzt, ist der Wert immer 0.
		 */
		inline void add(const T& element) { theSet.insert(element); }

		//! F�gt ein Element hinzu
		/**
		 * @param element	Das zu entfernende Element
		 */
		inline void remove(const T& element) { theSet.erase(element);	}

		//! F�gt ein Element hinzu
		inline irr::u32 count() { return theSet.size(); }

		//! Ermittelt, ob ein Element registriert ist
		/*
		 * @param id	Das zu Testende Element
		 * @returns		true, wenn das Element gefunden wurde, ansonsten false
		 */
		inline bool contains(const T& element) const { return theSet.find(element) != theSet.end(); }
		
		//! Ermittelt, ob der Manager leer ist
		inline bool isEmpty() const { return theSet.empty(); }

		//! Leert den Manager
		inline void clear() { theSet.clear(); }

		//! Iteriert die Klasse
		/**
		 * @param iterateFunction	Die aufzurufende Funktion
		 */
		template<typename TState>
		void iterate(void(*iterateFunction)(const T&, TState*), TState* userState = NULL) {
			ASSERT(iterateFunction);

			// Elemente durchlaufen
			typename std::set<T*>::const_iterator iterator;
			for (iterator = theSet.begin(); iterator != theSet.end(); ++iterator) {
				T element = &(*iterator).second;
			
				// Funktion aufrufen
				iterateFunction(element, userState);
			}
		}

	private:

		//! Das Set
		std::set<T> theSet;
	};

}}

#endif
