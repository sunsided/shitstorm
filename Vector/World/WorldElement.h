/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _WORLDELEMENT_H
#define _WORLDELEMENT_H

#include "global.h"
#include "Physics/IUpdateWorldTransform.h"

namespace pv {
namespace world {

	//! Ein Element in der Spielwelt
	class WorldElement : protected physics::IUpdateWorldTransform
	{
	public:
		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElement() {}
		
		//! Destruktor
		virtual ~WorldElement(void) {}

	protected:

		//! Ermittelt die aktuelle Welttransformation.
		/**
		 * @param worldTrans	Die aktuelle Welttransformation
		 */
		virtual void getWorldTransform(btTransform& worldTrans ) const {
		}

		//! Aktualisiert die Welttransformation.
		/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
		 * @param worldTrans	Die zu setzende Transformation
		 */
		virtual void setWorldTransform(const btTransform& worldTrans) {
		}

	private:

		//! Der Irrlicht-Szenenknoten
		irr::scene::ISceneNode* sceneNode;

	};

}}

#endif