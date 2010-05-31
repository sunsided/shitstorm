/** 
 * Project Vector
 * Physikkörper-Bewegungszustand
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _UPDATINGPHYSICSMOTIONSTATE_H
#define _UPDATINGPHYSICSMOTIONSTATE_H

#include "global.h"
#include "PhysicsMotionState.h"

namespace pv {
namespace physics {

	//! Bewegungszustand eines Körpers
	class UpdatingPhysicsMotionState : public PhysicsMotionState
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		UpdatingPhysicsMotionState(
			irr::scene::ISceneNode* sceneNode = NULL,
			const btTransform& startTrans = btTransform::getIdentity(),
			const btTransform& centerOfMassOffset = btTransform::getIdentity()) 
			: PhysicsMotionState(startTrans, centerOfMassOffset)
		{
			setSceneNode(sceneNode);
		}

		//! Erzeugt eine neue Instanz des Objektes
		UpdatingPhysicsMotionState(
			irr::scene::ISceneNode* sceneNode,
			const irr::core::matrix4& startTrans, 
			const irr::core::matrix4& centerOfMassOffset) 
			: PhysicsMotionState(conversion::toBtTransform(startTrans), conversion::toBtTransform(centerOfMassOffset)) 
		{
			setSceneNode(sceneNode);
		}

		//! Destruktor
		virtual ~UpdatingPhysicsMotionState(void);

		//! Aktualisiert die Welttransformation.
		/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
		 * @param worldTrans	Die zu setzende Transformation
		 */
		inline virtual void setWorldTransform(const btTransform& worldTrans);

		//! Liefert den verknüpften SceneNode
		inline irr::scene::ISceneNode* getSceneNode() const { 
			return reinterpret_cast<irr::scene::ISceneNode*>(m_userPointer);
		}

		//! Setzt den verknüpften SceneNode
		inline void setSceneNode(irr::scene::ISceneNode* sceneNode) { 
			m_userPointer = sceneNode;
		}

	};

}}

#endif
