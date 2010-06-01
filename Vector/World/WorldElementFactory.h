/** 
 * Project Vector
 * Ein Welt-Element
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _WORLDELEMENTFACTORY_H
#define _WORLDELEMENTFACTORY_H

#include "global.h"
#include "WorldElement.h"
#include "Physics/PhysicsWorld.h"
#include "SceneNodes/SceneObject.h"

namespace pv {
namespace world {

	//! Ein Element in der Spielwelt
	class WorldElementFactory
	{
	private:
		//! Erzeugt eine neue Instanz der WorldElement-Klasse
		WorldElementFactory();
		
		//! Destruktor
		virtual ~WorldElementFactory(void);
	
	public:

		//! Erzeugt einen beliebigen Knoten
		static WorldElement* CreateElement(physics::PhysicsWorld* world, nodes::SceneObject* sceneObject, btCollisionShape* shape, f32 mass = 0.0f, core::vector3df initialPosition = core::vector3df(0, 0, 0));

		//! Erzeugt einen beliebigen Knoten
		static WorldElement* CreateElement(physics::PhysicsWorld* world, scene::ISceneNode* sceneNode, btCollisionShape* shape, f32 mass = 0.0f, core::vector3df initialPosition = core::vector3df(0, 0, 0));

		//! Erzeugt einen Würfel-Knoten
		static WorldElement* CreateCubeElement(physics::PhysicsWorld* world, scene::ISceneManager* mgr, scene::ISceneNode* parent = 0, f32 mass = 0.0f, f32 size = 1.0f, s32 id = -1, core::vector3df initialPosition = core::vector3df(0, 0, 0));

	};

}}

#endif