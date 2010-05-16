#pragma once
#ifndef _CUBENODE_H
#define _CUBENODE_H

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class CubeNode : public ISceneNode
{
public:
	CubeNode(f32 size, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id) { initCube(size, size, size); }
	CubeNode(f32 width, f32 height, f32 depth, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id) { initCube(width, height, depth); }
	~CubeNode(void);

	virtual void render();

	virtual const aabbox3d<f32>& getBoundingBox() const { return Box; } 
	virtual s32 getMaterialCount() { return 1; }
	virtual SMaterial& getMaterial(s32 i) { return Material; }
	virtual void OnRegisterSceneNode();

private:
	void initCube(f32 width, f32 height, f32 depth);

private:
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[8];
	video::SMaterial Material;
};

#endif