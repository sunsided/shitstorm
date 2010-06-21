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
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(size, size, quads, quads); }

		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 size, u8 quadsW, u8 quadsH, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(size, size, quadsW, quadsH); }
		
		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quads, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quads, quads); }

		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quadsW, u8 quadsH, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quadsW, quadsH); }

		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quads, f32 uEnd, f32 vEnd, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quads, quads, 0.0f, uEnd, 0.0f, vEnd); }

		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quadsW, u8 quadsH, f32 uEnd, f32 vEnd, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quadsW, quadsH, 0.0f, uEnd, 0.0f, vEnd); }

		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quads, f32 uStart, f32 uEnd, f32 vStart, f32 vEnd, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quads, quads, uStart, uEnd, vStart, vEnd); }
		
		//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
		PlaneSceneNode(f32 width, f32 height, u8 quadsW, u8 quadsH, f32 uStart, f32 uEnd, f32 vStart, f32 vEnd, ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quadsW, quadsH, uStart, uEnd, vStart, vEnd); }

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
		void initPlane(f32 width, f32 height, u8 quadsW = 1, u8 quadsH = 1, f32 uStart = 0.0f, f32 uEnd = 1.0f, f32 vStart = 0.0f, f32 vEnd = 1.0f);

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