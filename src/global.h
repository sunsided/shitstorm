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

// Fix für std::min() und std::max() unter Windows
#define NOMINMAX

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

// 360 / (2*PI)
#ifndef GRAD_PI 
#define GRAD_PI 57.295779513082320876798154814105
#endif

// (2*PI) / 360
#ifndef INV_GRAD_PI
#define INV_GRAD_PI 0.01745329251994329576923690768489
#endif

#endif