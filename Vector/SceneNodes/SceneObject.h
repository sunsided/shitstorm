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

namespace pv {
namespace nodes {

	//! Ein Szenenobjekt
	class SceneObject
	{
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

	private:

		//! Der Szenenknoten
		irr::scene::ISceneNode* sceneNode;

	};

}}

#endif