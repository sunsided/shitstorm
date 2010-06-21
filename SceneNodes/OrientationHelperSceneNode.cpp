/** 
 * Project Vector
 * Scenenode, der einen Orientierungshelfer zur Verfügung stellt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "OrientationHelperSceneNode.h"

using namespace core;

namespace pv {
namespace nodes
{
	//! Erzeugt eine neue Instanz der OrientationHelperSceneNode-Klasse
	OrientationHelperSceneNode::OrientationHelperSceneNode(f32 helperSize, scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id), size(helperSize)
	{ 
		boundingBox = core::aabbox3d<f32>(-size*0.5f, -size*0.5f, -size*0.5f, size*1.5f, size*1.5f, size*1.5f);

		// Materialien erzeugen
		boxMaterial.Lighting = false;
		boxMaterial.Thickness = 2.0f;
		boxMaterial.Wireframe = true;
		boxMaterial.FrontfaceCulling = false;
		boxMaterial.BackfaceCulling = false;
	}

	//! Rendert den Knoten
	void OrientationHelperSceneNode::render() {
		
		// Rendern vorbereiten
		video::IVideoDriver* driver = SceneManager->getVideoDriver();
		driver->setMaterial(boxMaterial);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		
		// Längen berechnen
		f32 halfSize = size*0.5f;
		f32 lineLength = 1.5f*size;
		f32 arrowOffset = -0.125f*size;
		f32 offsetLine = lineLength - 0.25f*size;

		// Vektor und Box erzeugen
		core::vector3df zero = vector3df(0, 0, 0);
		core::aabbox3d<f32> box(-halfSize, -halfSize, -halfSize, halfSize, halfSize, halfSize);

		// Box zeichnen
		driver->draw3DBox(box);

		// X-Pfeil
		video::SColor color = video::SColor(255, 255, 0, 0);
		driver->draw3DLine(zero, vector3df(lineLength, 0, 0), color);

		core::triangle3df triangle(
			core::vector3df(offsetLine, -arrowOffset, 0),
			core::vector3df(offsetLine, arrowOffset, 0),
			core::vector3df(lineLength, 0, 0));
		driver->draw3DTriangle(triangle, color);

		triangle = core::triangle3df(
			core::vector3df(offsetLine, 0, -arrowOffset),
			core::vector3df(offsetLine, 0, arrowOffset),
			core::vector3df(lineLength, 0, 0));
		driver->draw3DTriangle(triangle, color);

		// Y-Pfeil
		color = video::SColor(255, 0, 255, 0);
		driver->draw3DLine(zero, vector3df(0, lineLength, 0), color);

		triangle = core::triangle3df(
			core::vector3df(-arrowOffset, offsetLine, 0),
			core::vector3df(arrowOffset, offsetLine, 0),
			core::vector3df(0, lineLength, 0));
		driver->draw3DTriangle(triangle, color);

		triangle = core::triangle3df(
			core::vector3df(0, offsetLine, -arrowOffset),
			core::vector3df(0, offsetLine, arrowOffset),
			core::vector3df(0, lineLength, 0));
		driver->draw3DTriangle(triangle, color);

		// Z-Pfeil
		color = video::SColor(255, 0, 0, 255);
		driver->draw3DLine(zero, vector3df(0, 0, lineLength), color);

		triangle = core::triangle3df(
			core::vector3df(-arrowOffset, 0, offsetLine),
			core::vector3df(arrowOffset, 0, offsetLine),
			core::vector3df(0, 0, lineLength));
		driver->draw3DTriangle(triangle, color);
		
		triangle = core::triangle3df(
			core::vector3df(0, -arrowOffset, offsetLine),
			core::vector3df(0, arrowOffset, offsetLine),
			core::vector3df(0, 0, lineLength));
		driver->draw3DTriangle(triangle, color);
	}

	//! Rotiert das Element so, dass seine Z-Achse in eine gegebene Richtung zeigt
	/** 
	* @direction		Die Richtung, in die X zeigen soll
	* @worldUp			Der Welt-Hoch-Vektor
	*/
	void OrientationHelperSceneNode::rotateZToDirection(const core::vector3df &direction, const core::vector3df &worldUp) {
		core::vector3df right = worldUp.crossProduct(direction).normalize();
		core::vector3df up = direction.crossProduct(right).normalize();

		// Create aim-at matrix from look-at matrix
		core::matrix4 mLookAt, m;
		mLookAt.buildCameraLookAtMatrixLH(core::vector3df(), direction, worldUp);
		mLookAt.getInverse(m);

		// Set the rotation
		core::vector3df rotation = m.getRotationDegrees();
		setRotation(rotation);
	}

}}