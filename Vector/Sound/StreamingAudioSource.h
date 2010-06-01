/** 
 * Project Vector
 * Audioquelle, die Daten streamt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */


#pragma once
#ifndef _STREAMINGAUDIOSOURCE_H
#define _STREAMINGAUDIOSOURCE_H

#include "global.h"
#include "AudioSource.h"

namespace pv {
namespace sound {

//! Audioquelle, die Daten streamt
class StreamingAudioSource : public AudioSource
{
public:
	//! Erzeugt eine neue Instanz des Objektes
	StreamingAudioSource(void);

	// Destruktor
	virtual ~StreamingAudioSource(void);
};

}}

#endif
