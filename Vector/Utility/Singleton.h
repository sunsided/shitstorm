/** 
 * Project Vector
 * Singleton
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SINGLETON_H
#define _SINGLETON_H

#include "global.h"

namespace pv {
namespace utility {

	//! Singleton
	template<typename C>
	class Singleton
	{
		friend class Cleanup;

	private:

		//! Helferklasse, die die Instanz löscht
		class Cleanup
		{
		public:
			//! Löscht die Singleton-Instanz
			~Cleanup() {
				if (Singleton<C>::_instance) { // TODO: Thread safety!
					delete Singleton<C>::_instance;
					Singleton<C>::_instance=NULL;
				}
			}
		};

		//! Die Singleton-Instanz
		static C* _instance;

		//! Copy-Konstruktor verbieten
		Singleton(const Singleton<C>&);

		//! Zuweisung verbieten
		Singleton& operator=(const Singleton &);

	protected:

		// protected-Konstruktor
		Singleton() {}

	public:

		//! Bezieht eine Instanz dieses Typs
		inline static C* get ()
		{
			static Cleanup cleanup;

			// TODO: Thread safety
			if (!_instance) _instance = new C ();
			return _instance;
		}

		// Vernichtet den Typ
		virtual ~Singleton () { _instance = 0; }
	};

	// Instanz initialisieren
	template <typename C> C* Singleton <C>::_instance = 0;

}}

#endif
