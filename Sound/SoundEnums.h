/** 
 * Project Vector
 * Sound-Enumerationen
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _SOUNDENUMS_H
#define _SOUNDENUMS_H

#include "global.h"

namespace pv {
namespace sound {

	//! Abspielzustand eines Liedes
	typedef enum ESoundPlayState {

		//! Kann abgespielt werden
		SPS_CANPLAY				= 0,

		//! Vom System angehalten und hat nicht gespielt
		SPS_SYSPAUSE_PAUSED		= 1,

		//! Vom System angehalten und hat gespielt
		SPS_SYSPAUSE_PLAYING	= 2,

		//! Vom System angehalten und war gestoppt
		SPS_SYSPAUSE_STOPPED	= 3

	} SoundPlayState;

}}

#endif
