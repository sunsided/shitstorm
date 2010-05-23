#include "GameTimer.h"

GameTimer::GameTimer(IrrlichtDevice *device) 
 : lastTime(-1), deltaT(0.0f), timerSpeed(0.0f)
{
	setTimer(device->getTimer());
}

GameTimer::GameTimer(ITimer *timer)
 : lastTime(-1), deltaT(0), timerSpeed(0.0f)
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