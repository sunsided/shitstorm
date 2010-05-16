#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"
#include "SceneNodes\CubeNode.h"
#include "SceneNodes\PlaneNode.h"

class Game : public Engine
{
public:
	Game(void);
	~Game(void);

protected:
	int setup();
	int teardown();
	void sceneLoop(int deltaT);

protected:
	ICameraSceneNode* camera;
	CubeNode* cube;
	ISceneNode* cubeLights[2];
	PlaneNode* plane;
};

#endif