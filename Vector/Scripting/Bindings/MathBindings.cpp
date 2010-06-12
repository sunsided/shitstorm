/** 
 * Project Vector
 * Mathematik-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "MathBindings.h"
#include <math.h>

using namespace Sqrat;
using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

namespace pv {
namespace scripting {
	
	//! Erzeugt eine Zufallszahl zwischen 0.0f und 1.0f
	inline irr::f32 randf() {
		const double low = 0.0f;
		const double high = 1.0f;
		return (rand() / (static_cast<float>(RAND_MAX) + 1.0f));
	}

	//! Erzeugt eine Zufallszahl zwischen 0.0f und 1.0f
	inline irr::f64 randd() {
		const double low = 0.0f;
		const double high = 1.0f;
		return (rand() / (static_cast<double>(RAND_MAX) + 1.0));
	}

	//! Bindet die ObjectClass-Klasse
	void MathBindings::scriptingBind(HSQUIRRELVM& vm) {
		
		RootTable(vm).Func(L"frand", &randf);
		RootTable(vm).Func(L"drand", &randd);

	}

}}
