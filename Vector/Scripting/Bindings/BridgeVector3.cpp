/** 
 * Project Vector
 * Vektor
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "BridgeVector3.h"

namespace pv {
namespace scripting {
	
	BridgeVector3 createVectorEx(irr::f32 x, irr::f32 y, irr::f32 z) {
		return BridgeVector3(x, y, z);
	}

	//! Bindet die EventClass-Klasse
	void BridgeVector3::scriptingBindBridgeVector(HSQUIRRELVM& vm) {

		using namespace Sqrat;
		using namespace irr::core;

		RootTable(vm).Bind(
			_SC("Vector3"),
			ImprovedClass<BridgeVector3, ImprovedAllocator<BridgeVector3>>(vm)
				.Ctor<irr::f32, irr::f32, irr::f32>()
				.Prop<irr::f32>(_SC("X"), &BridgeVector3::getX, &BridgeVector3::setX)
				.Prop<irr::f32>(_SC("Y"), &BridgeVector3::getY, &BridgeVector3::setZ)
				.Prop<irr::f32>(_SC("Z"), &BridgeVector3::getY, &BridgeVector3::setZ)
				.Func(_SC("getLength"), &BridgeVector3::getLength)
				.Func(_SC("getLengthSQ"), &BridgeVector3::getLengthSQ)
				.Func(_SC("setLength"), &BridgeVector3::setLength)
				.Func(_SC("normalize"), &BridgeVector3::normalize)
				.Func(_SC("dot"), &BridgeVector3::dotProduct)
				.Func(_SC("cross"), &BridgeVector3::crossProduct)
				.Func(_SC("scale"), &BridgeVector3::scale)
				.Func(_SC("_add"), &BridgeVector3::operator+)
				.Func(_SC("_sub"), &BridgeVector3::operator-)
				.Func(_SC("_mul"), &BridgeVector3::operator*)
				.Func(_SC("_modulo"), &BridgeVector3::crossProduct)
				.Func(_SC("_div"), &BridgeVector3::operator/)
				.Func(_SC("_cmp"), &BridgeVector3::operator==)
				.Func(_SC("_unm"), &BridgeVector3::getNegated)
				.Func(_SC("_tostring"), &BridgeVector3::toString)
				.Func(_SC("rotationToDirection"), &BridgeVector3::rotationToDirection)
				.Func(_SC("getSphericalCoordinateAngles"), &BridgeVector3::getSphericalCoordinateAngles)
				.Func(_SC("getHorizontalAngle"), &BridgeVector3::getHorizontalAngle)
				.Func(_SC("interpolate"), &BridgeVector3::interpolate)
				.Func(_SC("getInterpolated"), &BridgeVector3::getInterpolated)
				.Func(_SC("getInterpolated_quadratic"), &BridgeVector3::getInterpolated_quadratic)
				.Func(_SC("rotateYZBy"), &BridgeVector3::rotateYZBy)
				.Func(_SC("rotateXYBy"), &BridgeVector3::rotateXYBy)
				.Func(_SC("rotateXZBy"), &BridgeVector3::rotateXZBy)
				.Func(_SC("isBetweenPoints"), &BridgeVector3::isBetweenPoints)
				.Func(_SC("getDistanceFrom"), &BridgeVector3::getDistanceFrom)
				.Func(_SC("getDistanceFromSQ"), &BridgeVector3::getDistanceFromSQ)
				.Func(_SC("set"), &BridgeVector3::set)
				.Func(_SC("equals"), &BridgeVector3::equals)
			);

		/*
		Script script;
		script.CompileFile(L"scripts/vectortest.nut");
		script.Run();
		*/
	}

}}
