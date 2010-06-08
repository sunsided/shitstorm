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
				.Func(_SC("scale"), &BridgeVector3::scale)
				.Func(_SC("_add"), &BridgeVector3::operator+)
				.Func(_SC("_sub"), &BridgeVector3::operator-)
				.Func(_SC("_mul"), &BridgeVector3::operator*)
				.Func(_SC("_div"), &BridgeVector3::operator/)
				.Func(_SC("_cmp"), &BridgeVector3::operator==)
				.Func(_SC("_unm"), &BridgeVector3::getNegated)
				.Func(_SC("_tostring"), &BridgeVector3::toString)
			);


		Script script;
		script.CompileFile(L"scripts/vectortest.nut");
		script.Run();

		/*
		SqPlus::SQClassDef<pv::scripting::BridgeVector3>(_T("Vector")).
			staticFunc(&pv::scripting::BridgeVector3::constructor_void,_T("constructor")).
			staticFunc(&pv::scripting::BridgeVector3::constructor_3f,	_T("constructor"))
			/*
			var(&pv::scripting::BridgeVector3::vector::X, "x").
			var(&pv::scripting::BridgeVector3::vector::Y, "y").
			var(&pv::scripting::BridgeVector3::vector::Z, "z")
			*/
			/*
			func(&pv::utility::BridgeVector3::crossProduct,			_T("crossProduct")).
			func(&pv::utility::BridgeVector3::dotProduct,			_T("dotProduct")).
			func(&pv::utility::BridgeVector3::getLength,			_T("getLength")).
			func(&pv::utility::BridgeVector3::getLengthSQ,			_T("getLengthSQ")).
			func(&pv::utility::BridgeVector3::getDistanceFromSQ,	_T("getDistanceFromSQ")).
			func(&pv::utility::BridgeVector3::isBetweenPoints,		_T("isBetweenPoints")).
			func(&pv::utility::BridgeVector3::normalize,			_T("normalize")).
			func(&pv::utility::BridgeVector3::setLength,			_T("setLength")).
			func(&pv::utility::BridgeVector3::invert,				_T("invert")).
			func(&pv::utility::BridgeVector3::rotateXZBy,			_T("rotateXZBy")).
			func(&pv::utility::BridgeVector3::rotateXYBy,			_T("rotateXYBy")).
			func(&pv::utility::BridgeVector3::rotateYZBy,			_T("rotateYZBy")).
			func(&pv::utility::BridgeVector3::getInterpolated,		_T("getInterpolated")).
			func(&pv::utility::BridgeVector3::getInterpolated_quadratic,_T("getInterpolated_quadratic")).
			func(&pv::utility::BridgeVector3::interpolate,			_T("interpolate")).
			func(&pv::utility::BridgeVector3::getHorizontalAngle,	_T("getHorizontalAngle")).
			func(&pv::utility::BridgeVector3::getSphericalCoordinateAngles,_T("getSphericalCoordinateAngles")).
			func(&pv::utility::BridgeVector3::rotationToDirection,	_T("rotationToDirection"))
			*/
			;
	}

}}
