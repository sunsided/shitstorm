#pragma once
#ifndef _PLANENODE_H
#define _PLANENODE_H

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class PlaneNode : public ISceneNode
{
public:
	PlaneNode(f32 size, u8 quads, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id), Vertices(NULL), Indices(NULL) { initPlane(size, size, quads); }
	PlaneNode(f32 width, f32 height, u8 quads, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id), Vertices(NULL), Indices(NULL) { initPlane(width, height, quads); }
	~PlaneNode(void);

	virtual void render();

	virtual const aabbox3d<f32>& getBoundingBox() const { return Box; }
	virtual s32 getMaterialCount() { return 1; }
	virtual SMaterial& getMaterial(s32 i) { return Material; }

private:
	void initPlane(f32 width, f32 height, u8 quads = 1);

private:
	u8 quads;
	u16 *Indices;
	u16 VertexCount;
	u16 TriangleCount;
	core::aabbox3d<f32> Box;
	video::S3DVertex *Vertices;
	video::SMaterial Material;
};

#endif