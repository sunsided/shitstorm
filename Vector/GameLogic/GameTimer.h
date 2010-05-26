/** 
 * Project Vector
 * Spiel-Timer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _GAMETIMER_H
#define _GAMETIMER_H

#include "global.h"

namespace pv {

	//! Timer-Klasse mit erweiterten Möglichkeiten
	class GameTimer
	{
	public:
		//! Erzeugt eine neue Instanz des Timers
		/** Übernimmt einen Timer
		 * @param device	Das Device, von dem der Timer bezogen werden soll
		 */
		GameTimer(irr::IrrlichtDevice *device);
		
		//! Erzeugt eine neue Instanz des Timers
		/** Übernimmt einen Timer
		 * @param timer		Der zu übernehmende Timer
		 */
		GameTimer(irr::ITimer *timer);
		
		//! Destruktor
		~GameTimer(void);
	
		//! Setzt den Timer
		/** Übernimmt einen Timer
		 * @param timer		Der zu übernehmende Timer
		 */
		void setTimer(irr::ITimer *timer);

		//! Setzt den Timer
		/** Übernimmt einen Timer
		 * @param device	Das Device, von dem der Timer bezogen werden soll
		 */
		void setTimer(irr::IrrlichtDevice *device);

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
		* Dieser Aufruf sollte einmal zu Beginn der Spielschleife aufgerufen werden 
		* @return Die Zeit seit dem letzten Update in Sekunden. Ist der Timer pausiert, ist das Ergebnis immer 0.
		*/
		inline irr::f32 update() {
			if (isPaused()) return 0.0f;

			irr::u32 time = timer->getTime();
			deltaT = (time - lastTime) * 0.001f;
			lastTime = time;

			// Zeit zurückgeben
			return deltaT;
		}

		/**! Ermittelt die vergangene Zeit zwischen den letzten beiden Aufrufen von update() */
		inline irr::f32 getLastFrameTimeInMs() const { return deltaT * 1000.0f; }

		/**! Ermittelt die vergangene Zeit zwischen den letzten beiden Aufrufen von update() */
		inline irr::f32 getLastFrameTime() const { return deltaT; }

	private:

		//! Der zugrundeliegende Timer
		irr::ITimer *timer;

		//! Die Zeit beim letzten Aufruf der update-Methode
		irr::u32 lastTime;

		// Die Zeitdifferenz zum letzten Aufruf von update()
		irr::f32 deltaT;

		// Die Geschwindigkeit des zugrundeliegenden Timers
		irr::f32 timerSpeed;
	};

}

#endif