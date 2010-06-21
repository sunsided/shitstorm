/** 
 * Project Vector
 * Manager mit Setimplementierung
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SETMANAGERP_H
#define _SETMANAGERP_H

#include "SetManager.h"

namespace pv {
namespace utility {

	//! Manager f�r beliebige Typen.
	/** Generelle Implementierung f�r Zeigertypen
	 */
	template <typename T>
	class SetManager<T*>
	{
	public:

		//! Erzeugt eine neue Instanz des Managers
		SetManager(bool deleteOnDestruction = false) : deleteOnDestruct(deleteOnDestruction) {}
		
		//! Destruktor
		~SetManager(void) { clear(deleteOnDestruct); }

		//! F�gt ein Element hinzu
		/**
		 * @param element	Das hinzuzuf�gende Element
		 * @returns Der Index des hinzugef�gten Elementes; Wird Indizierung nicht unterst�tzt, ist der Wert immer 0.
		 */
		inline void add(T* element) { theSet.insert(element); }

		//! F�gt ein Element hinzu
		/**
		 * @param element	Das zu entfernende Element
		 */
		inline void remove(T* element) { theSet.erase(element);	}

		//! F�gt ein Element hinzu
		inline irr::u32 count() { return theSet.size(); }

		//! Ermittelt, ob ein Element registriert ist
		/*
		 * @param id	Das zu Testende Element
		 * @returns		true, wenn das Element gefunden wurde, ansonsten false
		 */
		inline bool contains(T* element) const { return theSet.find(element) != theSet.end(); }
		
		//! Ermittelt, ob der Manager leer ist
		inline bool isEmpty() const { return theSet.empty(); }

		//! Leert den Manager
		void clear(bool deleteOnDestruct = false) {

			// Ggf. die Elemente l�schen
			if (deleteOnDestruct) {
				typename std::set<irr::u32, T*>::const_iterator iterator;
				for (iterator = theSet.begin(); iterator != theSet.end(); ++iterator) {
					T* element = (*iterator).second;
					if (element) delete element;
				}
			}

			// Eigentlich nicht n�tig, aber hey.
			theSet.clear();
		}

		//! Iteriert die Klasse
		/**
		 * @param iterateFunction	Die aufzurufende Funktion
		 */
		template<typename TState>
		void iterate(void(*iterateFunction)(T*, TState*), TState* userState = NULL) {
			ASSERT(iterateFunction);

			// Elemente durchlaufen
			typename std::set<irr::u32, T*>::const_iterator iterator;
			for (iterator = theSet.begin(); iterator != theSet.end(); ++iterator) {
				T* element = (*iterator).second;
			
				// Funktion aufrufen
				iterateFunction(element, userState);
			}
		}

	private:

		//! Das Set
		std::set<T*> theSet;

		//! Gibt an, ob die Klasse beim Vernichten die Elemente l�schen soll
		bool deleteOnDestruct;
	};

}}

#endif
