#include "GameTimer.h"

GameTimer::GameTimer(IrrlichtDevice *device) 
 : lastTime(0), deltaT(0)
{
	setTimer(device->getTimer());
}

GameTimer::GameTimer(ITimer *timer)
 : lastTime(0), deltaT(0)
{
	setTimer(timer);
}

void GameTimer::setTimer(ITimer *timer) {
	this->timer = timer;
}

void GameTimer::setTimer(IrrlichtDevice *device) {
	setTimer(device->getTimer());
}

GameTimer::~GameTimer() {
}