/** 
 * Project Vector
 * Ein Szenenobjekt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _SCENEOBJECT_H
#define _SCENEOBJECT_H

#include "global.h"
#include "Scripting/Bindings/SceneBindings.h"

namespace pv {
namespace nodes {

	//! Ein Szenenobjekt
	class SceneObject
	{
		friend class scripting::SceneBindings;

	public:

		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		SceneObject(irr::scene::ISceneNode* node = NULL) : sceneNode(node) {}
		
		//! Destruktor
		virtual ~SceneObject(void);

	public:

		//! Wandelt das WorldElement in einen SceneNode um
		inline operator irr::scene::ISceneNode*() const {
			return sceneNode;
		}

		//! Ermittelt den Szenenknoten
		inline irr::scene::ISceneNode* getSceneNode() const {
			return sceneNode;
		}

		//! Setzt den Szenenknoten
		inline void setSceneNode(irr::scene::ISceneNode* node) {
			sceneNode = node;
		}

		//! Setzt die Sichtbarkeit des Knotens
		inline void setVisibility(const bool& visible) { sceneNode->setVisible(visible); }

		//! Setzt die Sichtbarkeit des Knotens
		inline bool getVisibility() const { return sceneNode->isVisible(); }

		//! Setzt die Sichtbarkeit des Knotens
		inline bool isTrulyVisible() const { return sceneNode->isTrulyVisible(); }

	private:

		// TODO: SceneObject sollte sein WorldObject kennen!

		//! Der Szenenknoten
		irr::scene::ISceneNode* sceneNode;

	};

}}

#endif