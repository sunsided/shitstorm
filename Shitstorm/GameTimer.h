#pragma once
#ifndef _GAMETIMER_H
#define _GAMETIMER_H

#include <irrlicht.h>
#include <assert.h>

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

	//! Pausiert die Spielzeit
	void pause() {
		if (isPaused()) return;
		timerSpeed = timer->getSpeed();
		timer->setSpeed(0.0f);
	}

	//! Fährt mit der Zeitmessung fort
	void unpause() {
		if (!isPaused()) return;
		timer->setSpeed(timerSpeed);
		timerSpeed = 0.0f;
	}

	//! Ermittelt, ob der Timer angehalten wurde
	inline bool isPaused() const { return timerSpeed > 0.0f; }

	/**! Aktualisiert den Timer
	* Dieser Aufruf sollte einmal zu Beginn der Spielschleife aufgerufen werden */
	inline void update() 
	{
		if (isPaused()) return;

		u32 time = timer->getTime();
		deltaT = (time - lastTime) * 0.001f;
		lastTime = time;

		assert(deltaT >= 0.0f);
	}

	/**! Ermittelt die vergangene Zeit zwischen den letzten beiden Aufrufen von update() */
	inline f32 getLastFrameTimeInMs() const { return deltaT * 1000.0f; }

	/**! Ermittelt die vergangene Zeit zwischen den letzten beiden Aufrufen von update() */
	inline f32 getLastFrameTime() const { return deltaT; }

private:
	ITimer *timer;
	u32 lastTime;
	f32 deltaT;
	f32 timerSpeed;
};

#endif