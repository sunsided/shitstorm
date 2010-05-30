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

#include "global.h"
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

		//! Rotiert das Element so, dass seine Z-Achse in eine gegebene Richtung zeigt
		/** 
		 * @direction		Die Richtung, in die X zeigen soll
		 * @worldUp			Der Welt-Hoch-Vektor
		 */
		void rotateZToDirection(const core::vector3df &direction, const core::vector3df &worldUp);

		//! Rotiert das Element so, dass seine Z-Achse in eine gegebene Richtung zeigt
		/** 
		 * @camera			Die Kamera, in deren Richtung das Objekt zeigen soll
		 * @worldUp			Der Welt-Hoch-Vektor
		 */
		inline void rotateZToDirection(const scene::ICameraSceneNode *camera, const core::vector3df &worldUp) {
			core::vector3df direction = (camera->getTarget() - camera->getPosition()).normalize();
			rotateZToDirection(direction, worldUp);
		}

		//! Rotiert das Element so, dass seine Z-Achse in eine gegebene Richtung zeigt
		/** 
		 * @camera			Die Kamera, in deren Richtung das Objekt zeigen soll
		 */
		inline void rotateZToDirection(const scene::ICameraSceneNode *camera) {
			core::vector3df worldUp = camera->getUpVector();
			rotateZToDirection(camera, worldUp);
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