#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"
#include "SceneNodes\CubeNode.h"
#include "SceneNodes\PlaneNode.h"

#pragma warning(push)
#pragma warning(disable: 4996) 
#include <pal/palFactory.h>
#pragma warning(pop)

class Game : public Engine
{
public:
	Game(void);
	~Game(void);

protected:
	int setup();
	int teardown();
	void sceneLoop(f32 deltaT, bool windowIsActive);
	void setupLoop();

protected:
	ICameraSceneNode* camera;
	CubeNode* cube;
	CubeNode* tinyCube;
	ILightSceneNode* cubeLights[2];
	PlaneNode* plane;
	
	palPhysics *physics;
	palBox *physicsBox;
	palBox *tinyPhysicsBox;
	palTerrainPlane *physicsPlane;
};

#endif