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

	//! Bindet die ObjectClass-Klasse
	void IrrlichtBindings::scriptingBind(HSQUIRRELVM& vm) {

		// dimension2df
		RootTable(vm).Bind(
			_SC("Dimension"),
			Class<dimension2df>(vm)
				.Func(_SC("getArea"), &dimension2df::getArea)
				.Func(_SC("getInterpolated"), &dimension2df::getInterpolated)
				.Func(_SC("_add"), &dimension2df::operator+)
				.Func<bool(dimension2df::*)(const dimension2df&)const>(_SC("_cmp"), &dimension2df::operator==)
				.Func(_SC("set"), &dimension2df::set)
			);

		// ISceneNode
		RootTable(vm).Bind(
			_SC("MaterialLayer"),
			Class<SMaterialLayer>(vm)
				.Var(_SC("AnisotropicFilter"), &SMaterialLayer::AnisotropicFilter)
				.Var(_SC("LODBias"), &SMaterialLayer::LODBias)
				.Var(_SC("Texture"), &SMaterialLayer::Texture)
			);

		// ISceneNode
		RootTable(vm).Bind(
			_SC("Material"),
			Class<SMaterial>(vm)
				.Var(_SC("AmbientColor"), &SMaterial::AmbientColor)
				.Var(_SC("AntiAliasing"), &SMaterial::AntiAliasing)
				.Func(_SC("getFlag"), &SMaterial::getFlag)
				.Func(_SC("setFlag"), &SMaterial::setFlag)
				//.Var(_SC("BackfaceCulling"), &SMaterial::BackfaceCulling)
				//.Var(_SC("ColorMask"), &SMaterial::ColorMask)
				.Var(_SC("DiffuseColor"), &SMaterial::DiffuseColor)
				.Var(_SC("EmissiveColor"), &SMaterial::EmissiveColor)
				//.Var(_SC("FogEnable"), &SMaterial::FogEnable)
				//.Var(_SC("FrontfaceCulling"), &SMaterial::FrontfaceCulling)
				//.Var(_SC("GouraudShading"), &SMaterial::GouraudShading)
				//.Var(_SC("Lighting"), &SMaterial::Lighting)
				.Var(_SC("MaterialType"), &SMaterial::MaterialType)
				.Var(_SC("MaterialTypeParam"), &SMaterial::MaterialTypeParam)
				.Var(_SC("MaterialTypeParam2"), &SMaterial::MaterialTypeParam2)
				.Prop(_SC("IsTransparent"), &SMaterial::isTransparent)
				//.Var(_SC("NormalizeNormals"), &SMaterial::NormalizeNormals)
				//.Var(_SC("PointCloud"), &SMaterial::PointCloud)
				.Var(_SC("Shininess"), &SMaterial::Shininess)
				.Var(_SC("SpecularColor"), &SMaterial::SpecularColor)
				//.Var(_SC("TextureLayer"), &SMaterial::TextureLayer)
				.Var(_SC("Thickness"), &SMaterial::Thickness)
				//.Var(_SC("Wireframe"), &SMaterial::Wireframe)
				.Var(_SC("ZBuffer"), &SMaterial::ZBuffer)
				//.Var(_SC("ZWriteEnable"), &SMaterial::ZWriteEnable)
				.Func(_SC("_cmp"), &SMaterial::operator==)
			);

		// ITexture
		RootTable(vm).Bind(
			_SC("ITexture"),
			Class<ITexture, NoConstructor>(vm)
				.Func(_SC("getColorFormat"), &ITexture::getColorFormat)
				.Func(_SC("getOriginalSize"), &ITexture::getOriginalSize)
				.Func(_SC("getSize"), &ITexture::getSize)
				.Prop(_SC("HasAlpha"), &ITexture::hasAlpha)
				.Prop(_SC("HasMipMaps"), &ITexture::hasMipMaps)
				.Prop(_SC("IsRenderTarget"), &ITexture::isRenderTarget)
			);

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
			_SC("Vector"),
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

		// line3df
		RootTable(vm).Bind(
			_SC("Line"),
			Class<line3df>(vm)
				.Var(_SC("Start"), &line3df::start)
				.Var(_SC("End"), &line3df::end)
				.Func(_SC("getClosestPoint"), &line3df::getClosestPoint)
				.Func(_SC("_modulo"), &line3df::getClosestPoint)
				//.Func(_SC("getIntersectionWithSphere"), &line3df::getIntersectionWithSphere)
				.Func(_SC("getLength"), &line3df::getLength)
				.Func(_SC("getLengthSQ"), &line3df::getLengthSQ)
				.Func(_SC("getMiddle"), &line3df::getMiddle)
				.Func(_SC("getVector"), &line3df::getVector)
				.Func(_SC("isPointBetweenStartAndEnd"), &line3df::isPointBetweenStartAndEnd)
				.Func(_SC("_add"), &line3df::operator+)
				.Func<void(line3df::*)(const vector3df&,const vector3df&)>(_SC("setLine"), &line3df::setLine)
			);

		// AABB
		RootTable(vm).Bind(
			_SC("Aabbox"),
			Class<aabbox3df>(vm)
				.Var(_SC("MinEdge"), &aabbox3df::MinEdge)
				.Var(_SC("MaxEdge"), &aabbox3df::MaxEdge)
				.Func(_SC("addInternalBox"), &aabbox3df::addInternalBox)
				.Func<void(aabbox3df::*)(const vector3df&)>(_SC("addInternalPoint"), &aabbox3df::addInternalPoint)
				.Func<void(aabbox3df::*)(const vector3df&)>(_SC("_add"), &aabbox3df::addInternalPoint)
				.Func(_SC("getArea"), &aabbox3df::getArea)
				.Func(_SC("getCenter"), &aabbox3df::getCenter)
				.Func(_SC("getExtent"), &aabbox3df::getExtent)
				.Func(_SC("getInterpolated"), &aabbox3df::getInterpolated)
				.Func(_SC("getVolume"), &aabbox3df::getVolume)
				.Func(_SC("intersectsWithBox"), &aabbox3df::intersectsWithBox)
				.Func<bool(aabbox3df::*)(const line3df&)const>(_SC("intersectsWithLine"), &aabbox3df::intersectsWithLine)
				.Func(_SC("isEmpty"), &aabbox3df::isEmpty)
				.Func(_SC("isFullInside"), &aabbox3df::isFullInside)
				.Func(_SC("isPointInside"), &aabbox3df::isPointInside)
				.Func(_SC("_modulo"), &aabbox3df::isPointInside)
				.Func(_SC("isPointTotalInside"), &aabbox3df::isPointTotalInside)
				.Func(_SC("_cmp"), &aabbox3df::operator==)
				.Func<void(aabbox3df::*)(irr::f32,irr::f32,irr::f32)>(_SC("reset"), &aabbox3df::reset)
			);

		// ISceneNode
		RootTable(vm).Bind(
			_SC("ISceneNode"),
			Class<ISceneNode, NoConstructor>(vm)
				.Func(_SC("addChild"), &ISceneNode::addChild)
				.Func(_SC("getAbsolutePosition"), &ISceneNode::getAbsolutePosition)
				.Func(_SC("getAbsoluteTransformation"), &ISceneNode::getAbsoluteTransformation)
				.Func(_SC("getAutomaticCulling"), &ISceneNode::getAutomaticCulling)
				.Func(_SC("getBoundingBox"), &ISceneNode::getBoundingBox)
				//.Func(_SC("getDebugName"), &ISceneNode::getDebugName)
				.Prop(_SC("Id"), &ISceneNode::getID)
				.Func(_SC("getMaterial"), &ISceneNode::getMaterial)
				.Func(_SC("getMaterialCount"), &ISceneNode::getMaterialCount)
				//.Func(_SC("getName"), &ISceneNode::getName)
				.Prop(_SC("Parent"), &ISceneNode::getParent)
				.Func(_SC("getPosition"), &ISceneNode::getPosition)
				.Func(_SC("ReferenceCount"), &ISceneNode::getReferenceCount)
				.Prop(_SC("Children"), &ISceneNode::getChildren)
				.Func(_SC("getRelativeTransformation"), &ISceneNode::getRelativeTransformation)
				.Func(_SC("getRotation"), &ISceneNode::getRotation)
				.Func(_SC("getScale"), &ISceneNode::getScale)
				.Prop(_SC("SceneManager"), &ISceneNode::getSceneManager)
				.Func(_SC("getTransformedBoundingBox"), &ISceneNode::getTransformedBoundingBox)
				.Func(_SC("getType"), &ISceneNode::getType)
				.Prop(_SC("DebugDataVisible"), &ISceneNode::isDebugDataVisible)
				.Prop(_SC("TrulyVisible"), &ISceneNode::isTrulyVisible)
				.Prop(_SC("Visible"), &ISceneNode::isVisible)
				.Func(_SC("setIsDebugObject"), &ISceneNode::setIsDebugObject)
				.Func(_SC("setDebugDataVisible"), &ISceneNode::setDebugDataVisible)
				.Func(_SC("setMaterialFlag"), &ISceneNode::setMaterialFlag)
				.Func(_SC("setMaterialTexture"), &ISceneNode::setMaterialTexture) // ITexture
				.Func(_SC("setMaterialType"), &ISceneNode::setMaterialType)
				.Func(_SC("setParent"), &ISceneNode::setParent)
				.Func(_SC("setPosition"), &ISceneNode::setPosition)
				.Func(_SC("setRotation"), &ISceneNode::setRotation)
				.Func(_SC("setScale"), &ISceneNode::setScale)
				.Func(_SC("setVisible"), &ISceneNode::setVisible)
				.Func(_SC("updateAbsolutePosition"), &ISceneNode::updateAbsolutePosition)
			);

		// ISceneManager
		RootTable(vm).Bind(
			_SC("ISceneManager"),
			Class<ISceneManager, NoConstructor>(vm)
				.Func(_SC("setActiveCamera"), &ISceneManager::setActiveCamera)
			);
	}

}}
