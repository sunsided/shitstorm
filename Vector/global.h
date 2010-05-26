/** 
 * Project Vector
 * Precompiled Header
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#ifndef _GLOBAL_H
#define _GLOBAL_H
#pragma once

// Irrlicht
#include <irrlicht.h>

// ASSERT()-Makro
#include <assert.h>
#ifndef ASSERT
	#if _DEBUG
		#define ASSERT(x) assert(x)
	#else
		#define ASSERT(x)
	#endif
#endif


#endif