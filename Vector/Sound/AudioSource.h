/** 
 * Project Vector
 * Audioquelle
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _AUDIOSOURCE_H
#define _AUDIOSOURCE_H

#include "global.h"

namespace pv {
namespace sound {

//! Audioquelle
class AudioSource
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	AudioSource(void);

	// Destruktor
	virtual ~AudioSource(void);
};

}}

#endif
