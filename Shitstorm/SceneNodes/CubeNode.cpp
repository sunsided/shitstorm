#include "CubeNode.h"
using namespace video;

#define TOP		0
#define BOTTOM	1
#define FRONT	2
#define BACK	3
#define LEFT	4
#define RIGHT	5

void CubeNode::initCube(f32 width, f32 height, f32 depth, u8 quads) 
{
	if(initialized) for (u8 i=1; i<6; ++i) delete Planes[i];
	initialized = true;

	Planes[TOP]		= new PlaneNode(width, depth, quads, this, SceneManager, 1);
	Planes[TOP]->setPosition(vector3df(0.0f, height/2.0f, 0.0f));

	Planes[BOTTOM]	= new PlaneNode(width, depth, quads, this, SceneManager, 1);
	Planes[BOTTOM]->setPosition(vector3df(0.0f, -height/2.0f, 0.0f));
	Planes[BOTTOM]->setRotation(vector3df(180.0f, 0.0f, 0.0f));

	Planes[FRONT]	= new PlaneNode(width, height, quads, this, SceneManager, 1);
	Planes[FRONT]->setPosition(vector3df(0.0f, 0.0f, -depth/2.0f));
	Planes[FRONT]->setRotation(vector3df(-90.0f, 0.0f, 0.0f));

	Planes[BACK]	= new PlaneNode(width, height, quads, this, SceneManager, 1);
	Planes[BACK]->setPosition(vector3df(0.0f, 0.0f, depth/2.0f));
	Planes[BACK]->setRotation(vector3df(90.0f, 0.0f, 0.0f));

	Planes[LEFT]	= new PlaneNode(depth, height, quads, this, SceneManager, 1);
	Planes[LEFT]->setPosition(vector3df(-width/2.0f, 0.0f, 0.0f));
	Planes[LEFT]->setRotation(vector3df(-90.0f, 90.0f, 0.0f));

	Planes[RIGHT]	= new PlaneNode(depth, height, quads, this, SceneManager, 1);
	Planes[RIGHT]->setPosition(vector3df(width/2.0f, 0.0f, 0.0f));
	Planes[RIGHT]->setRotation(vector3df(-90.0f, -90.0f, 0.0f));

	// Bounding Box bauen
	Box.reset(0, 0, 0);
	for (s32 i=1; i<6; ++i)
	{
		Box.addInternalBox(Planes[i]->getBoundingBox());
	}
}

CubeNode::~CubeNode(void)
{
	if(initialized) for (u8 i=1; i<6; ++i) delete Planes[i];
}

void CubeNode::render() 
{
	for (u8 i=1; i<6; ++i)
	{
		Planes[i]->render();
	}
}

void CubeNode::OnRegisterSceneNode() 
{
	SceneManager->registerNodeForRendering(this);
	ISceneNode::OnRegisterSceneNode();
}