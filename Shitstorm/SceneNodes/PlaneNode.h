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
	PlaneNode(f32 size, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id) { initPlane(size, size); }
	PlaneNode(f32 width, f32 height, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id) { initPlane(width, height); }
	~PlaneNode(void);

	virtual void render();

	virtual const aabbox3d<f32>& getBoundingBox() const { return Box; } 
	virtual s32 getMaterialCount() { return 1; }
	virtual SMaterial& getMaterial(s32 i) { return Material; }

private:
	void initPlane(f32 width, f32 height);

private:
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;
};

#endif