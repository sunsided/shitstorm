/** 
 * Project Vector
 * Vektor
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "BridgeVector3.h"

#include "Scripting/Scripting.h"
#include "Scripting/ScriptingVM.h"

namespace pv {
namespace scripting {

	//! Bindet die EventClass-Klasse
	void BridgeVector3::scriptingBindBridgeVector() {

		using namespace Sqrat;

		HSQUIRRELVM vm = ScriptingVM::getVM();

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
