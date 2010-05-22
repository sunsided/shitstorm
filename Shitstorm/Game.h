#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"
#include "SceneNodes\CubeNode.h"
#include "SceneNodes\PlaneNode.h"

#include <pal/palFactory.h>

class Game : public Engine
{
public:
	Game(void);
	~Game(void);

protected:
	int setup();
	int teardown();
	void sceneLoop(int deltaT);
	void setupLoop();

protected:
	ICameraSceneNode* camera;
	CubeNode* cube;
	ISceneNode* cubeLights[2];
	PlaneNode* plane;
	
	palPhysics *physics;
	palBox *physicsBox;
	palTerrainPlane *physicsPlane;
};

#endif