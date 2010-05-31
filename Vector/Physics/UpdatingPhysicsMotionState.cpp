/** 
 * Project Vector
 * Physikkörper-Bewegungszustand
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "UpdatingPhysicsMotionState.h"

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

		irr::scene::ISceneNode* node = getSceneNode();
		if (!node) return;

		// http://www.daniweb.com/forums/thread284877.html
		irr::core::matrix4 matrix;
		worldTrans.getOpenGLMatrix(matrix.pointer());
		node->setRotation(matrix.getRotationDegrees());
		node->setPosition(matrix.getTranslation());
	}

	//! Setzt den verknüpften SceneNode
	void UpdatingPhysicsMotionState::setSceneNode(irr::scene::ISceneNode* sceneNode) { 
		m_userPointer = sceneNode;
		if (!sceneNode) return;
			
		// http://www.daniweb.com/forums/thread284877.html
		irr::core::matrix4 matrix;
		btTransform worldTrans;
		getWorldTransform(worldTrans);
		worldTrans.getOpenGLMatrix(matrix.pointer());
		sceneNode->setRotation(matrix.getRotationDegrees());
		sceneNode->setPosition(matrix.getTranslation());
	}

}}
