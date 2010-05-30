/** 
 * Project Vector
 * Interface für Klassen, die Welttransformationen unterstützen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _IUPDATEWORLDTRANSFORM_H
#define _IUPDATEWORLDTRANSFORM_H

#include "global.h"

#include <btBulletDynamicsCommon.h>

namespace pv {
namespace physics {

	//! Interface für Klassen, die Welttransformationen unterstützen
	class IUpdateWorldTransform {
	
	protected:
		//! Konstruktor verstecken
		inline IUpdateWorldTransform() {}

		//! Destruktor ausblenden
		inline virtual ~IUpdateWorldTransform() = 0;

	public:

		//! Ermittelt die aktuelle Welttransformation.
		/**
		 * @param worldTrans	Die aktuelle Welttransformation
		 */
		virtual void getWorldTransform(btTransform& worldTrans ) const = 0;

		//! Aktualisiert die Welttransformation.
		/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
		 * @param worldTrans	Die zu setzende Transformation
		 */
		virtual void setWorldTransform(const btTransform& worldTrans) = 0;

	};
	
}}

#endif
