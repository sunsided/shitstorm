/** 
 * Project Vector
 * Sound State
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "SoundState.h"

#include <al.h>
#include <iostream>
#include "Scripting/Scripting.h"

namespace pv {
namespace sound {

	SoundState::~SoundState(void)
	{
	}

	//! Setzt den Doppler-Faktor
	void SoundState::setDopplerFactor(irr::f32 factor) const {
		alDopplerFactor(factor);
	}

	//! Setzt die Schallgeschwindigkeit
	void SoundState::setSpeedOfSound(irr::f32 speed) const {
		alSpeedOfSound(speed);
	}

	//! Setzt das Distanzmodell
	void SoundState::setDistanceModel(SoundDistanceModel model) const {
		alDistanceModel((ALenum)model);
	}

	//! Ruft das Init-Event auf, falls es existiert
	/* @returns true, wenn das Event aufgerufen wurde, ansonsten false. */
	bool SoundState::callInitEventIfExists() {
		using namespace Sqrat;

		HSQUIRRELVM vm = DefaultVM::Get();
		Function function(RootTable(vm), _SC("OnInitSoundState"));
		if (function.IsNull()) return false;
		try {
			function.Execute();
		}
		catch(Exception e) {
			std::wcerr << "Fehler beim Ausführen des Events 'OnInitSoundState': " << e.Message() << std::endl;
		}
		catch(...) {
			std::wcerr << "Fehler beim Ausführen des Events 'OnInitSoundState'." << std::endl;
		}
		return true;
	}

}}