#pragma once
#ifndef _GAMETIMER_H
#define _GAMETIMER_H

#include <irrlicht.h>
using namespace irr;

class GameTimer
{
public:
	GameTimer(IrrlichtDevice *device);
	GameTimer(ITimer *timer);
	~GameTimer(void);
	
	/**! Setzt den Timer erneut */
	void setTimer(ITimer *timer);

	/**! Setzt den Timer erneut */
	void setTimer(IrrlichtDevice *device);

	/**! Setzt den Timer zurück */
	void reset() { lastTime = deltaT = 0; }

	/**! Aktualisiert den Timer
	* Dieser Aufruf sollte einmal zu Beginn der Spielschleife aufgerufen werden */
	void update() 
	{
		u32 time = timer->getTime();
		deltaT = time - lastTime;
		lastTime = time;
	}

	/**! Ermittelt die vergangene Zeit zwischen den letzten beiden Aufrufen von update() */
	u32 getLastFrameTime() { return deltaT; }

private:
	ITimer *timer;
	u32 lastTime;
	u32 deltaT;
};

#endif