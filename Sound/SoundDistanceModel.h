/** 
 * Project Vector
 * Sound-Distanzmodell nach OpenAL
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDDISTANCEMODEL_H
#define _SOUNDDISTANCEMODEL_H

#include "global.h"

#include <al.h>

namespace pv {
namespace sound {

	//! Das Sound-Distanzmodell nach OpenAL
	typedef enum ESoundDistanceModel {

		SDM_NONE = 0,
		SDM_INVERSE_DISTANCE = AL_INVERSE_DISTANCE,
		SDM_INVERSE_DISTANCE_CLAMPED = AL_INVERSE_DISTANCE_CLAMPED,
		SDM_LINEAR_DISTANCE = AL_LINEAR_DISTANCE,
		SDM_LINEAR_DISTANCE_CLAMPED = AL_LINEAR_DISTANCE_CLAMPED,
		SDM_EXPONENT_DISTANCE = AL_EXPONENT_DISTANCE,
		SDM_EXPONENT_DISTANCE_CLAMPED = AL_EXPONENT_DISTANCE_CLAMPED,

	} SoundDistanceModel;

}}

#endif
