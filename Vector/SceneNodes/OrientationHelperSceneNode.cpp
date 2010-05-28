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
	}

	//! Rendert den Knoten
	void OrientationHelperSceneNode::render() {
		
		// Rendern vorbereiten
		video::IVideoDriver* driver = SceneManager->getVideoDriver();
		driver->setMaterial(getMaterial(0));
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		
		// Längen berechnen
		f32 halfSize = size*0.5f;
		f32 lineLength = 1.5*size;
		f32 arrowOffset = -0.125f*size;
		f32 offsetLine = lineLength - 0.25*size;

		// Vektor und Box erzeugen
		core::vector3df zero = vector3df(0, 0, 0);
		core::aabbox3d<f32> box(-halfSize, -halfSize, -halfSize, halfSize, halfSize, halfSize);

		// Box zeichnen
		driver->setMaterial(boxMaterial);
		driver->draw3DBox(box);

		// X-Pfeil
		video::SColor color = video::SColor(255, 255, 0, 0);
		driver->draw3DLine(zero, vector3df(lineLength, 0, 0), color);
		driver->draw3DLine(vector3df(offsetLine, -arrowOffset, 0), vector3df(offsetLine, arrowOffset, 0), color);
		driver->draw3DLine(vector3df(offsetLine, 0, -arrowOffset), vector3df(offsetLine, 0, arrowOffset), color);
		driver->draw3DLine(vector3df(offsetLine, -arrowOffset, 0), vector3df(lineLength, 0, 0), color);
		driver->draw3DLine(vector3df(offsetLine, arrowOffset, 0), vector3df(lineLength, 0, 0), color);
		driver->draw3DLine(vector3df(offsetLine, 0, -arrowOffset), vector3df(lineLength, 0, 0), color);
		driver->draw3DLine(vector3df(offsetLine, 0, arrowOffset), vector3df(lineLength, 0, 0), color);

		// Y-Pfeil
		color = video::SColor(255, 0, 255, 0);
		driver->draw3DLine(zero, vector3df(0, lineLength, 0), color);
		driver->draw3DLine(vector3df(-arrowOffset, offsetLine, 0), vector3df(arrowOffset, offsetLine, 0), color);
		driver->draw3DLine(vector3df(0, offsetLine, -arrowOffset), vector3df(0, offsetLine, arrowOffset), color);
		driver->draw3DLine(vector3df(-arrowOffset, offsetLine, 0), vector3df(0, lineLength, 0), color);
		driver->draw3DLine(vector3df(arrowOffset, offsetLine, 0), vector3df(0, lineLength, 0), color);
		driver->draw3DLine(vector3df(0, offsetLine, -arrowOffset), vector3df(0, lineLength, 0), color);
		driver->draw3DLine(vector3df(0, offsetLine, arrowOffset), vector3df(0, lineLength, 0), color);

		// Z-Pfeil
		color = video::SColor(255, 0, 0, 255);
		driver->draw3DLine(zero, vector3df(0, 0, lineLength), color);
		driver->draw3DLine(vector3df(-arrowOffset, 0, offsetLine), vector3df(arrowOffset, 0, offsetLine), color);
		driver->draw3DLine(vector3df(0, -arrowOffset, offsetLine), vector3df(0, arrowOffset, offsetLine), color);
		driver->draw3DLine(vector3df(-arrowOffset, 0, offsetLine), vector3df(0, 0, lineLength), color);
		driver->draw3DLine(vector3df(arrowOffset, 0, offsetLine), vector3df(0, 0, lineLength), color);
		driver->draw3DLine(vector3df(0, -arrowOffset, offsetLine), vector3df(0, 0, lineLength), color);
		driver->draw3DLine(vector3df(0, arrowOffset, offsetLine), vector3df(0, 0, lineLength), color);
	}

	//! Rotiert die Helferkamera so, dass sie der Sicht der Hauptkamera auf dieses Objekt entspräche.
	/** 
	* @mainCamera		Die Hauptkamera
	* @helperCamera		Die Helferkamera
	*/
	void OrientationHelperSceneNode::rotateHelperToFaceMainView(const scene::ICameraSceneNode *mainCamera, scene::ICameraSceneNode *helperCamera) const {
		ASSERT(mainCamera); ASSERT(helperCamera);

		// GetAbsolutePosition() liefert (0,0,0), wenn das Element versteckt ist
		rotateHelperToFaceMainView(mainCamera->getPosition(), mainCamera->getTarget(), helperCamera);
	}

	//! Rotiert die Helferkamera so, dass sie der Sicht der Hauptkamera auf dieses Objekt entspräche.
	/** 
	* @mainCameraPosition		Die Position der Hauptkamera
	* @mainCameraTarget		Die Zielposition der Hauptkamera
	* @helperCamera			Die Helferkamera
	*/
	void OrientationHelperSceneNode::rotateHelperToFaceMainView(const core::vector3df &mainCameraPosition, const core::vector3df &mainCameraTarget, scene::ICameraSceneNode *helperCamera) const {
		ASSERT(helperCamera);

		// GetAbsolutePosition() liefert (0,0,0), wenn das Element versteckt ist
		f32 distance = helperCamera->getPosition().getDistanceFrom(getPosition());
		//core::vector3df direction = (mainCameraPosition - mainCameraTarget).normalize();
		core::vector3df direction = (mainCameraPosition - getPosition()).normalize();
		core::vector3df newPosition = getPosition() + direction*distance;
		helperCamera->setPosition(newPosition);
	}

}}