#pragma once
#ifndef _PLANENODE_H
#define _PLANENODE_H

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

namespace pv {

	class PlaneNode : public ISceneNode
	{
	public:
		PlaneNode(ISceneNode* parent, ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { }
		PlaneNode(f32 size, u8 quads, ISceneNode* parent, ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(size, size, quads); }
		PlaneNode(f32 width, f32 height, u8 quads, ISceneNode* parent, ISceneManager* mgr, s32 id)
			: ISceneNode(parent, mgr, id), Mesh(NULL) { initPlane(width, height, quads); }
		virtual ~PlaneNode(void);

		virtual void render();

		virtual const aabbox3d<f32>& getBoundingBox() const { return Box; }
		virtual u32 getMaterialCount() { return 1; }
		virtual SMaterial& getMaterial(u32 i) { return Material; }
		virtual void OnRegisterSceneNode();

		const IMesh* getMesh() const { return Mesh; }

	private:
		void initPlane(f32 width, f32 height, u8 quads = 1, f32 uStart = 0.0f, f32 uEnd = 1.0f, f32 vStart = 0.0f, f32 vEnd = 1.0f);

	private:
		u8 quads;
		//u16 *Indices;
		u16 VertexCount;
		u16 TriangleCount;
		IMesh *Mesh;
		core::aabbox3d<f32> Box;
		//video::S3DVertex *Vertices;
		video::SMaterial Material;
	};

}

#endif