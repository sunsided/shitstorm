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

// Vorwärtsdeklaration der Klassen
namespace nodes { class SceneObject; }

namespace physics {

	//! Bewegungszustand eines Körpers
	class UpdatingPhysicsMotionState : public PhysicsMotionState
	{
	public:
		//! Erzeugt eine neue Instanz des Objektes
		UpdatingPhysicsMotionState(
			nodes::SceneObject* sceneObject = NULL,
			const btTransform& startTrans = btTransform::getIdentity(),
			const btTransform& centerOfMassOffset = btTransform::getIdentity()) 
			: PhysicsMotionState(startTrans, centerOfMassOffset)
		{
			setSceneObject(sceneObject);
		}

		//! Erzeugt eine neue Instanz des Objektes
		UpdatingPhysicsMotionState(
			nodes::SceneObject* sceneObject,
			const irr::core::matrix4& startTrans, 
			const irr::core::matrix4& centerOfMassOffset) 
			: PhysicsMotionState(conversion::toBtTransform(startTrans), conversion::toBtTransform(centerOfMassOffset)) 
		{
			setSceneObject(sceneObject);
		}

		//! Destruktor
		virtual ~UpdatingPhysicsMotionState(void);

		//! Aktualisiert die Welttransformation.
		/** Bullet ruft diese Funktion nur auf, wenn das Objekt aktiv ist.
		 * @param worldTrans	Die zu setzende Transformation
		 */
		inline virtual void setWorldTransform(const btTransform& worldTrans);

		//! Liefert den verknüpften SceneNode
		nodes::SceneObject* getSceneObject();

		//! Setzt den verknüpften SceneNode
		void setSceneObject(nodes::SceneObject* sceneObject);

	};

}}

#endif
