/** 
 * Project Vector
 * Spiel-Timer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "GameTimer.h"

namespace pv {

	//! Erzeugt eine neue Instanz des Timers
	/** Übernimmt einen Timer
	* @param device	Das Device, von dem der Timer bezogen werden soll
	*/
	GameTimer::GameTimer(irr::IrrlichtDevice *device) 
	 : lastTime(-1), deltaT(0.0f), timerSpeed(0.0f), timer(NULL)
	{
		setTimer(device->getTimer());
	}

	//! Erzeugt eine neue Instanz des Timers
	/** Übernimmt einen Timer
	* @param timer		Der zu übernehmende Timer
	*/
	GameTimer::GameTimer(irr::ITimer *timer)
	 : lastTime(-1), deltaT(0), timerSpeed(0.0f), timer(NULL)
	{
		setTimer(timer);
	}

	//! Setzt den Timer
	/** Übernimmt einen Timer
	* @param timer		Der zu übernehmende Timer
	*/
	void GameTimer::setTimer(irr::ITimer *timer) {
		if (this->timer) this->timer->drop();
		this->timer = timer;
		timer->grab();
	}

	//! Setzt den Timer
	/** Übernimmt einen Timer
	* @param device	Das Device, von dem der Timer bezogen werden soll
	*/
	void GameTimer::setTimer(irr::IrrlichtDevice *device) {
		setTimer(device->getTimer());
	}

	//! Destruktor
	GameTimer::~GameTimer() {
	}

}