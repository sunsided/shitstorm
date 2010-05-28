/** 
 * Project Vector
 * SceneNode, der eine Ebene zur Verfügung stellt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PLANESCENENODE_H
#define _PLANESCENENODE_H

#include "global.h"
using namespace irr;

namespace pv {
namespace nodes {

	class PlaneSceneNode : public scene::ISceneNode
	{
	public:
		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { }
		
		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 size, u8 quads, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(size, size, quads); }
		
		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quads, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quads); }
		
		//! Destruktor
		virtual ~PlaneSceneNode(void);

		//! Rendert den Scenenode
		virtual void render();

		//! Ermittelt die Bounding Box
		inline virtual const core::aabbox3d<f32>& getBoundingBox() const { return Box; }

		//! Liefert die Anzahl der Materialien
		inline virtual u32 getMaterialCount() { return 1; }

		//! Liefert das Material mit der gegebenen ID
		inline virtual video::SMaterial& getMaterial(u32 i) { return Material; }

		//! Reagiert auf das RegisterSceneNode-Ereignis
		virtual void OnRegisterSceneNode();

		//! Liefert den Mesh
		inline const scene::IMesh* getMesh() const { return Mesh; }

	private:
		
		//! Initialisiert die Ebene
		void initPlane(f32 width, f32 height, u8 quads = 1, f32 uStart = 0.0f, f32 uEnd = 1.0f, f32 vStart = 0.0f, f32 vEnd = 1.0f);

	private:

		// Die Anzahl der Vertices
		u16 VertexCount;
		
		// Die Anzahl der Dreieicke
		u16 TriangleCount;
		
		// Das Mesh der Ebene
		scene::IMesh *Mesh;

		//! Die Bounding Box
		core::aabbox3d<f32> Box;

		//! Das Material
		video::SMaterial Material;
	};

}}

#endif