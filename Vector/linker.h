/** 
 * Project Vector
 * Linker-Hints für Windows
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#ifndef _LINKER_H
#define _LINKER_H
#pragma once

#include "global.h"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")

	#ifdef HIDE_CONSOLE
		#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#if _MSC_VER
	#pragma comment(lib, "BulletCollision.lib")
	#pragma comment(lib, "BulletDynamics.lib")
	#pragma comment(lib, "LinearMath.lib")
#endif

#endif
