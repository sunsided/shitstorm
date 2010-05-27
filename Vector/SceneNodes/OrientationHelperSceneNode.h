/** 
 * Project Vector
 * Scenenode, der einen Orientierungshelfer zur Verfügung stellt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _ORIENTATIONHELPERSCENENODE_H
#define _ORIENTATIONHELPERSCENENODE_H

#include <irrlicht.h>
using namespace irr;

namespace pv {
namespace nodes {

	class OrientationHelperSceneNode : public scene::ISceneNode
	{
	public:
		//! Erzeugt eine neue Instanz der OrientationHelperSceneNode-Klasse
		OrientationHelperSceneNode(f32 size, scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
		
		//! Destruktor
		virtual ~OrientationHelperSceneNode(void) {}

		//! Rendert den Scenenode
		virtual void render();

		//! Ermittelt die Bounding Box
		inline virtual const core::aabbox3d<f32>& getBoundingBox() const { return boundingBox; }
		
		//! Reagiert auf das RegisterSceneNode-Ereignis
		inline virtual void OnRegisterSceneNode() {
			if (!isVisible()) return;

			SceneManager->registerNodeForRendering(this);
			ISceneNode::OnRegisterSceneNode();
		}

	private:

		//! Die Bounding Box
		core::aabbox3d<f32> boundingBox;

		//! Die Größe des Helfers
		f32 size;

		//! Das Material der Box
		video::SMaterial boxMaterial;
	};

}}

#endif