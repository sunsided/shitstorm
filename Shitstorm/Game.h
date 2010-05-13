#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"
#include "SceneNodes\CubeNode.h"

class Game : public Engine
{
public:
	Game(void);
	~Game(void);

protected:
	int setup();
	void sceneLoop(int deltaT);

protected:
	ICameraSceneNode* camera;
	CubeNode* cube;
};

#endif