/** 
 * Project Vector
 * Initialisierungsparameter der Engine
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#ifndef _ENGINEINITIALIZATIONPARAMS_H
#define _ENGINEINITIALIZATIONPARAMS_H
#pragma once

#include "global.h"

namespace pv {

	//! Grafiktreiber-Enumeration
	typedef enum EVideoDriver {
		
		//! DirectX
		VD_DIRECTX,

		//! OpenGL
		VD_OPENGL,

		//! Software-Renderer
		VD_SOFTWARE,

		//! Intern
		/** @internal Die Anzahl der Werte der EEngineStatusCode-Enumeration */
		VD_COUNT

	} VideoDriver;

	//! Parameter für die Initialisierung der Engine
	typedef struct SEngineInitializationParams {

		//! Der Fenstertitel
		wchar_t *windowTitle;

		//! Die Größe des Fensters
		irr::core::dimension2d<irr::u32> screenSize;

		//! Gibt an, ob die Anwendung im Vollbild gestartet werden soll
		bool fullscreen;

		//! Anzahl der Bits pro Pixel
		irr::u8 bitsPerPixel;

		//! Der zu verwendende Grafiktreiber
		VideoDriver driver;

		//! Initialisiert die Struktur
		SEngineInitializationParams() :
			windowTitle(L"Project Vector"),
			fullscreen(false), 
			bitsPerPixel(16), 
			screenSize(irr::core::dimension2d<irr::u32>(640, 480)), 
#ifdef WIN32
			driver(VD_DIRECTX)
#else
			driver(VD_OPENGL)
#endif
		{}

	} EngineInitializationParams;

}

#endif