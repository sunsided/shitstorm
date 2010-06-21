/** 
 * Project Vector
 * Physikk�rper-Bewegungszustand
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "UpdatingPhysicsMotionState.h"
#include "SceneNodes/SceneObject.h"

namespace pv {
namespace physics {
	
	//! Destruktor
	UpdatingPhysicsMotionState::~UpdatingPhysicsMotionState(void) {}

	//! Aktualisiert die Welttransformation.
	/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
	* @param worldTrans	Die zu setzende Transformation
	*/
	void UpdatingPhysicsMotionState::setWorldTransform(const btTransform& worldTrans) {
		PhysicsMotionState::setWorldTransform(worldTrans);

		nodes::SceneObject* sceneObject = getSceneObject();
		if (!sceneObject) return;

		// http://www.daniweb.com/forums/thread284877.html
		irr::core::matrix4 matrix;
		worldTrans.getOpenGLMatrix(matrix.pointer());
		sceneObject->getSceneNode()->setRotation(matrix.getRotationDegrees());
		sceneObject->getSceneNode()->setPosition(matrix.getTranslation());
	}

	//! Setzt den verkn�pften SceneNode
	void UpdatingPhysicsMotionState::setSceneObject(nodes::SceneObject* sceneObject) { 
		m_userPointer = sceneObject;
		if (!sceneObject) return;
			
		// http://www.daniweb.com/forums/thread284877.html
		irr::core::matrix4 matrix;
		btTransform worldTrans;
		getWorldTransform(worldTrans);
		worldTrans.getOpenGLMatrix(matrix.pointer());
		sceneObject->getSceneNode()->setRotation(matrix.getRotationDegrees());
		sceneObject->getSceneNode()->setPosition(matrix.getTranslation());
	}

	//! Liefert den verkn�pften SceneNode
	nodes::SceneObject* UpdatingPhysicsMotionState::getSceneObject() { 
		return reinterpret_cast<nodes::SceneObject*>(m_userPointer);
	}

}}
