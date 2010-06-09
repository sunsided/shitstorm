/** 
 * Project Vector
 * Irrlicht-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "IrrlichtBindings.h"
#include "BridgeVector3.h"
#include "Scripting/Sqrat/sqratImpClass.h"

using namespace Sqrat;
using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

namespace pv {
namespace scripting {
	
	// Werte setzen
	inline irr::core::vector3df& setVectorValue(irr::core::vector3df* instance, f32 x, f32 y, f32 z) {
		return instance->set(x, y, z);
	}

	// Vektor addieren
	inline irr::core::vector3df addVector(irr::core::vector3df* instance, const irr::core::vector3df& b) {
		return vector3df(*instance + b);
	}

	// Vektor subtrahieren
	inline irr::core::vector3df subVector(irr::core::vector3df* instance, const irr::core::vector3df& b) {
		return vector3df(*instance - b);
	}

	// Vektor skalieren
	inline irr::core::vector3df mulVector(irr::core::vector3df* instance, const irr::f32& b) {
		return vector3df(*instance * b);
	}

	// Vektor skalieren
	inline irr::core::vector3df divVector(irr::core::vector3df* instance, const irr::f32& b) {
		return vector3df(*instance / b);
	}

	// Vektor kompatibilisieren (yeah!)
	inline BridgeVector3 convertToCompatibleVector(irr::core::vector3df* instance) {
		BridgeVector3 vector = BridgeVector3(*instance);
		return vector;
	}
	
	//! Gibt eine String-Darstellung des Vektors wieder
	inline std::wstring vectorToString(irr::core::vector3df* instance) { 
		irr::core::stringw str = L"{";
		str += instance->X;
		str += L", ";
		str += instance->Y;
		str += L", ";
		str += instance->Z;
		str += L"}";

		std::wstring stdstring;
		stdstring.append(str.c_str());
		return stdstring;
	}

	//! Bindet die EventClass-Klasse
	void IrrlichtBindings::scriptingBind(HSQUIRRELVM& vm) {

		// Farben
		RootTable(vm).Bind(
			_SC("Color"),
			Class<SColor>(vm)
				.Func(_SC("getAlpha"), &SColor::getAlpha)
				.Func(_SC("getRed"), &SColor::getRed)
				.Func(_SC("getGreen"), &SColor::getGreen)
				.Func(_SC("getBlue"), &SColor::getBlue)
				.Func(_SC("getLightness"), &SColor::getLightness)
				.Func(_SC("getLuminance"), &SColor::getLuminance)
				.Func(_SC("getAverage"), &SColor::getAverage)
				.Func(_SC("setAlpha"), &SColor::setAlpha)
				.Func(_SC("setRed"), &SColor::setRed)
				.Func(_SC("setGreen"), &SColor::setGreen)
				.Func(_SC("setBlue"), &SColor::setBlue)
				.Func(_SC("toA1R5G5B5"), &SColor::toA1R5G5B5)
				.Func(_SC("_chk"), &SColor::operator==)
				.Func(_SC("_add"), &SColor::operator+)
				.Func<void (SColor::*)(u32,u32,u32,u32)>(_SC("set"), &SColor::set)
				.Func<void (SColor::*)(u32)>(_SC("setAll"), &SColor::set)
				.Func(_SC("getInterpolated"), &SColor::getInterpolated)
				.Func(_SC("getInterpolated_quadratic"), &SColor::getInterpolated_quadratic)
				.Func(_SC("getInterpolated"), &SColor::getInterpolated_quadratic)
			);

		// Farben
		RootTable(vm).Bind(
			_SC("ColorF"),
			Class<SColorf>(vm)
				.Var(_SC("r"), &SColorf::r)
				.Var(_SC("g"), &SColorf::g)
				.Var(_SC("b"), &SColorf::b)
				.Var(_SC("a"), &SColorf::a)
				.Func(_SC("toColor"), &SColorf::toSColor)
				.Func(_SC("getAlpha"), &SColorf::getAlpha)
				.Func(_SC("getRed"), &SColorf::getRed)
				.Func(_SC("getGreen"), &SColorf::getGreen)
				.Func(_SC("getBlue"), &SColorf::getBlue)
				.Func(_SC("setColorComponentValue"), &SColorf::setColorComponentValue)
				.Func<void (SColorf::*)(f32,f32,f32,f32)>(_SC("setARGB"), &SColorf::set)
				.Func(_SC("getInterpolated"), &SColorf::getInterpolated)
				.Func(_SC("getInterpolated_quadratic"), &SColorf::getInterpolated_quadratic)
				.Func(_SC("getInterpolated"), &SColorf::getInterpolated_quadratic)
			);

		// Vektor
		RootTable(vm).Bind(
			_SC("vector3df"),
			ImprovedClass<vector3df, ImprovedAllocator<vector3df>>(vm)
				.Ctor<irr::f32, irr::f32, irr::f32>()
				.Var(_SC("X"), &vector3df::X)
				.Var(_SC("Y"), &vector3df::Y)
				.Var(_SC("Z"), &vector3df::Z)
				.Func(_SC("getLength"), &vector3df::getLength)
				.Func(_SC("getLengthSQ"), &vector3df::getLengthSQ)
				.Func(_SC("setLength"), &vector3df::setLength)
				.Func(_SC("normalize"), &vector3df::normalize)
				.Func(_SC("dot"), &vector3df::dotProduct)
				.Func(_SC("cross"), &vector3df::crossProduct)
				.GlobalFunc(_SC("_add"), &addVector)
				.GlobalFunc(_SC("_sub"), &subVector)
				.GlobalFunc(_SC("_mul"), &mulVector)
				.GlobalFunc(_SC("_div"), &divVector)
				.Func(_SC("_modulo"), &vector3df::crossProduct)
				.Func(_SC("_cmp"), &vector3df::operator==)
				.Func(_SC("_unm"), &vector3df::invert)
				.Func(_SC("equals"), &vector3df::operator==)
				.Func(_SC("rotationToDirection"), &vector3df::rotationToDirection)
				.Func(_SC("getSphericalCoordinateAngles"), &vector3df::getSphericalCoordinateAngles)
				.Func(_SC("getHorizontalAngle"), &vector3df::getHorizontalAngle)
				.Func(_SC("interpolate"), &vector3df::interpolate)
				.Func(_SC("getInterpolated"), &vector3df::getInterpolated)
				.Func(_SC("getInterpolated_quadratic"), &vector3df::getInterpolated_quadratic)
				.Func(_SC("rotateYZBy"), &vector3df::rotateYZBy)
				.Func(_SC("rotateXYBy"), &vector3df::rotateXYBy)
				.Func(_SC("rotateXZBy"), &vector3df::rotateXZBy)
				.Func(_SC("isBetweenPoints"), &vector3df::isBetweenPoints)
				.Func(_SC("getDistanceFrom"), &vector3df::getDistanceFrom)
				.Func(_SC("getDistanceFromSQ"), &vector3df::getDistanceFromSQ)
				.GlobalFunc(_SC("_tostring"), &vectorToString)
				.GlobalFunc(_SC("set"), &setVectorValue)
				//.GlobalFunc(_SC("toCompatibleVector"), &convertToCompatibleVector)
			);
	}

}}
