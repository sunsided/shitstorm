/** 
 * Project Vector
 * Statuscodes der Engine
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#ifndef _ENGINESTATUSCODE_H
#define _ENGINESTATUSCODE_H
#pragma once

namespace pv {

	//! Statuscodes der Game-Engine
	typedef enum EEngineStatusCode {
		
		//! Vorgang erfolgreich abgeschlossen
		ESC_SUCCESS = 0,

		//! Die Instanzierung der Engine ist fehlgeschlagen
		ESC_INSTANCIATION_FAILED = 1,

		//! Das Erzeugen des Irrlicht-Devices ist fehlgeschlagen
		ESC_DEVICE_CREATION_FAILED = 2,

		//! Das Beziehen des Videotreibers ist fehlgeschlagen
		ESC_VIDEO_DRIVER_FAILED = 3,

		//! Das Beziehen des Szenenmanagers ist fehlgeschlagen
		ESC_SMGR_FAILED = 4,

		//! Das Beziehen der GUI-Umgebung ist fehlgeschlagen
		ESC_GUIENV_FAILED = 5,

		//! Ein notwendiges Feature wurde nicht von der Hardware bereitgestellt
		ESC_FEATURE_FAILED = 6,

		//! Das Physikmanagement konnte nicht initialisiert werden
		ESC_PHYSICS_FAILED = 7,

		//! Das Weltmanagement konnte nicht initialisiert werden
		ESC_WORLDMGMT_FAILED = 8,

		//! Eine Physikwelt konnte nicht erzeugt werden
		ESC_PHYSICSWORLD_FAILED = 9,

		//! Ein weiterer Szenenmanager konnte nicht erzeugt werden
		ESC_AUX_SMGR_FAILED = 10,

		//! Soundmanager konnte nicht initialisiert werden
		ESC_SOUND_FAILED = 11,

		//! Sounddevice konnte nicht initialisiert werden
		ESC_SOUND_DEVICE_FAILED = 12,

		//! Soundkontext konnte nicht initialisiert werden
		ESC_SOUND_CONTEXT_FAILED = 13,

		//! Sound-Listener konnte nicht initialisiert werden
		ESC_SOUND_LISTENER_FAILED = 14,

		//! Die Script-VM ist auf's Maul geflogen
		ESC_SCRIPTVM_FAILED = 15,

		//! Intern
		/** @internal Die Anzahl der Werte der EEngineStatusCode-Enumeration */
		ESC_COUNT

	} EngineStatusCode;

}

#endif