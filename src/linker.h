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

// Konsole ausblenden
#ifdef HIDE_CONSOLE
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


// Irrlicht-Library
#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
#endif


// Bullet
#if _MSC_VER
	#pragma comment(lib, "BulletCollision.lib")
	#pragma comment(lib, "BulletDynamics.lib")
	#pragma comment(lib, "LinearMath.lib")
#endif


// OpenAL
#if _MSC_VER
	#pragma comment(lib, "OpenAL32.lib")
	#if _DEBUG
		#pragma comment(lib, "liboggd.lib")
		#pragma comment(lib, "libvorbisd.lib")
		#pragma comment(lib, "libvorbisfiled.lib")
	#else
		#pragma comment(lib, "libogg.lib")
		#pragma comment(lib, "libvorbis.lib")
		#pragma comment(lib, "libvorbisfile.lib")
	#endif
#endif


// Squirrel
#ifdef _MSC_VER
	#ifdef UNICODE
		#define LIB  "U.lib"
	#else
		#define LIB  ".lib"
	#endif

	#ifdef _DEBUG

		#pragma comment(lib,"squirrelD" LIB)
		#pragma comment(lib,"sqstdlibD" LIB)

	#else

		#pragma comment(lib,"squirrel" LIB)
		#pragma comment(lib,"sqstdlib" LIB)

#endif
#endif


#endif
