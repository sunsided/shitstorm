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
	
	//! Bindet die ObjectClass-Klasse
	void IrrlichtBindings::scriptingBindEnums(HSQUIRRELVM& vm) {

		RootTable(vm).Bind(
			_SC("ComparisonFunc"),
			Enumeration(vm)
				.Const(_SC("Never"), ECFN_NEVER)
				.Const(_SC("LessEqual"), ECFN_LESSEQUAL)
				.Const(_SC("Equal"), ECFN_EQUAL)
				.Const(_SC("Less"), ECFN_LESS)
				.Const(_SC("NotEqual"), ECFN_NOTEQUAL)
				.Const(_SC("GreaterEqual"), ECFN_GREATEREQUAL)
				.Const(_SC("Greater"), ECFN_GREATER)
				.Const(_SC("Always"), ECFN_ALWAYS)
			);

		RootTable(vm).Bind(
			_SC("ColorPlane"),
			Enumeration(vm)
				.Const(_SC("Never"), ECP_NONE)
				.Const(_SC("Alpha"), ECP_ALPHA)
				.Const(_SC("Red"), ECP_RED)
				.Const(_SC("Green"), ECP_GREEN)
				.Const(_SC("Blue"), ECP_BLUE)
				.Const(_SC("RGB"), ECP_RGB)
				.Const(_SC("All"), ECP_ALL)
				.Const(_SC("RG"), ECP_RED | ECP_GREEN)
				.Const(_SC("GB"), ECP_GREEN | ECP_BLUE)
				.Const(_SC("RB"), ECP_RED | ECP_BLUE)
			);

		RootTable(vm).Bind(
			_SC("ColorMaterial"),
			Enumeration(vm)
				.Const(_SC("None"), ECM_NONE)
				.Const(_SC("Diffuse"), ECM_DIFFUSE)
				.Const(_SC("Ambient"), ECM_AMBIENT)
				.Const(_SC("Emissive"), ECM_EMISSIVE)
				.Const(_SC("Specular"), ECM_SPECULAR)
				.Const(_SC("DiffuseAmbient"), ECM_DIFFUSE_AND_AMBIENT)
			);

		RootTable(vm).Bind(
			_SC("AntiAliasingMode"),
			Enumeration(vm)
				.Const(_SC("None"), EAAM_OFF)
				.Const(_SC("Simple"), EAAM_SIMPLE)
				.Const(_SC("Quality"), EAAM_QUALITY)
				.Const(_SC("LineSmooth"), EAAM_LINE_SMOOTH)
				.Const(_SC("PointSmooth"), EAAM_POINT_SMOOTH)
				.Const(_SC("FullBasic"), EAAM_FULL_BASIC)
				.Const(_SC("AlphaToCoverage"), EAAM_ALPHA_TO_COVERAGE)
			);

		RootTable(vm).Bind(
			_SC("AlphaSource"),
			Enumeration(vm)
				.Const(_SC("None"), EAS_NONE)
				.Const(_SC("VertexColor"), EAS_VERTEX_COLOR)
				.Const(_SC("Texture"), EAS_TEXTURE)
			);

		RootTable(vm).Bind(
			_SC("ModulateFunction"),
			Enumeration(vm)
				.Const(_SC("Modulate1X"), EMFN_MODULATE_1X)
				.Const(_SC("Modulate2X"), EMFN_MODULATE_2X)
				.Const(_SC("Modulate4X"), EMFN_MODULATE_4X)
			);

		RootTable(vm).Bind(
			_SC("BlendFactor"),
			Enumeration(vm)
				.Const(_SC("Zero"), EBF_ZERO)
				.Const(_SC("One"), EBF_ONE)
				.Const(_SC("DstColor"), EBF_DST_COLOR)
				.Const(_SC("OneMinusDstColor"), EBF_ONE_MINUS_DST_COLOR)
				.Const(_SC("SrcColor"), EBF_SRC_COLOR)
				.Const(_SC("OneMinusSrcColor"), EBF_ONE_MINUS_SRC_COLOR)
				.Const(_SC("SrcAlpha"), EBF_SRC_ALPHA)
				.Const(_SC("OneMinusSrcAlpha"), EBF_ONE_MINUS_SRC_ALPHA)
				.Const(_SC("DstAlpha"), EBF_DST_ALPHA)
				.Const(_SC("OneMinusDstAlpha"), EBF_ONE_MINUS_DST_ALPHA)
				.Const(_SC("SrcAlphaSaturate"), EBF_SRC_ALPHA_SATURATE)
			);

		RootTable(vm).Bind(
			_SC("MaterialType"),
			Enumeration(vm)
				.Const(_SC("Solid"), EMT_SOLID)
				.Const(_SC("Solid2Layer"), EMT_SOLID_2_LAYER)
				.Const(_SC("Lightmap"), EMT_LIGHTMAP)
				.Const(_SC("LightmapAdd"), EMT_LIGHTMAP_ADD)
				.Const(_SC("LightmapM2"), EMT_LIGHTMAP_M2)
				.Const(_SC("LightmapM4"), EMT_LIGHTMAP_M4)
				.Const(_SC("LightmapLighting"), EMT_LIGHTMAP_LIGHTING)
				.Const(_SC("LightmapLightingM2"), EMT_LIGHTMAP_LIGHTING_M2)
				.Const(_SC("LightmapLightingM4"), EMT_LIGHTMAP_LIGHTING_M4)
				.Const(_SC("DetailMap"), EMT_DETAIL_MAP)
				.Const(_SC("SphereMap"), EMT_SPHERE_MAP)
				.Const(_SC("Reflection2Layer"), EMT_REFLECTION_2_LAYER)
				.Const(_SC("TransparentAddColor"), EMT_TRANSPARENT_ADD_COLOR)
				.Const(_SC("TransparentAlpha"), EMT_TRANSPARENT_ALPHA_CHANNEL)
				.Const(_SC("TransparentAlphaRef"), EMT_TRANSPARENT_ALPHA_CHANNEL_REF)
				.Const(_SC("TransparentVertexAlpha"), EMT_TRANSPARENT_VERTEX_ALPHA)
				.Const(_SC("TransparentReflection2Layer"), EMT_TRANSPARENT_REFLECTION_2_LAYER)
				.Const(_SC("NormalMapSolid"), EMT_NORMAL_MAP_SOLID)
				.Const(_SC("NormalMapTransparentAddColor"), EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR)
				.Const(_SC("NormalMapTransparentVertexAlpha"), EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA)
				.Const(_SC("ParallaxMapSolid"), EMT_PARALLAX_MAP_SOLID)
				.Const(_SC("ParallaxMapAddColor"), EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR)
				.Const(_SC("ParallaxMapVertexAlpha"), EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA)
				.Const(_SC("OneTextureBlend"), EMT_ONETEXTURE_BLEND)
			);

		RootTable(vm).Bind(
			_SC("MaterialFlag"),
			Enumeration(vm)
				.Const(_SC("Wireframe"), EMF_WIREFRAME)
				.Const(_SC("PointCloud"), EMF_POINTCLOUD)
				.Const(_SC("GouraudShading"), EMF_GOURAUD_SHADING)
				.Const(_SC("Lighting"), EMF_LIGHTING)
				.Const(_SC("ZBuffer"), EMF_ZBUFFER)
				.Const(_SC("ZWrite"), EMF_ZWRITE_ENABLE)
				.Const(_SC("BackfaceCulling"), EMF_BACK_FACE_CULLING)
				.Const(_SC("FrontfaceCulling"), EMF_FRONT_FACE_CULLING)
				.Const(_SC("BilinearFilter"), EMF_BILINEAR_FILTER)
				.Const(_SC("TrilinearFilter"), EMF_TRILINEAR_FILTER)
				.Const(_SC("AnisotropicFilter"), EMF_ANISOTROPIC_FILTER)
				.Const(_SC("Fog"), EMF_FOG_ENABLE)
				.Const(_SC("NormalizeNormals"), EMF_NORMALIZE_NORMALS)
				.Const(_SC("TextureWrap"), EMF_TEXTURE_WRAP)
				.Const(_SC("AntiAliasing"), EMF_ANTI_ALIASING)
				.Const(_SC("ColorMask"), EMF_COLOR_MASK)
				.Const(_SC("ColorMaterial"), EMF_COLOR_MATERIAL)
			);
	}

}}
