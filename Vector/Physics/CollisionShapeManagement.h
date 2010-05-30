/** 
 * Project Vector
 * Verwaltung der Collision Shapes
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _COLLISIONSHAPEMANAGEMENT_H
#define _COLLISIONSHAPEMANAGEMENT_H

#include "global.h"
#include <vector>

// Vorwärtsdeklaration der Klassen
class btCollisionShape;

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine verwaltet
	class CollisionShapeManagement
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		CollisionShapeManagement(void) {}

		//! Destruktor
		virtual ~CollisionShapeManagement(void);

		//! Registriert ein Collision Shape
		/** Alle hier registrierten Shapes werden automatisch vom System vernichtet.
		 *	Ein zusätzlicher Aufruf von delete ist nicht nötig!
		 * @param world		Die hinzuzufügende Welt
		 * @returns Die Nummer des Collision Shapes
		 */
		unsigned int registerCollisionShape(const btCollisionShape* shape);

		//! Ermittelt ein Collision Shape anhand seiner ID
		const btCollisionShape* getCollisionShape(unsigned int collisionShapeId);

		//! Liefert die Anzahl der registrierten Elemente
		inline std::vector<const btCollisionShape*>::size_type count() const { return collisionShapes.capacity(); }
		
	private:
		
		//! Vernichtet die Dynamikwelt
		void destruct();

	private:

		//! Sammlung aller Shapes
		std::vector<const btCollisionShape*> collisionShapes;

	};

}}

#endif
