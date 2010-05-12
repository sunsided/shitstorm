#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"

class Game : public Engine
{
public:
	Game(void);
	~Game(void);

protected:
	int setup();
	void sceneLoop();
};

#endif