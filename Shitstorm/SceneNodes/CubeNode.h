#pragma once
#ifndef _CUBENODE_H
#define _CUBENODE_H

#include <irrlicht.h>
#include "PlaneNode.h"
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class CubeNode : public ISceneNode
{
public:
	CubeNode(f32 size, u8 quads, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id), initialized(false) { initCube(size, size, size, quads); }
	CubeNode(f32 width, f32 height, f32 depth, u8 quads, ISceneNode* parent, ISceneManager* mgr, s32 id)
		: ISceneNode(parent, mgr, id), initialized(false) { initCube(width, height, depth, quads); }
	virtual ~CubeNode(void);

	virtual void render();

	virtual const aabbox3d<f32>& getBoundingBox() const { return Box; } 
	virtual s32 getMaterialCount() { return 6; }
	virtual SMaterial& getMaterial(s32 i) { return Planes[i]->getMaterial(0); }
	virtual void OnRegisterSceneNode();
	
private:
	void initCube(f32 width, f32 height, f32 depth, u8 quads = 2);

private:
	core::aabbox3d<f32> Box;
	PlaneNode *Planes[6];
	bool initialized;
};

#endif