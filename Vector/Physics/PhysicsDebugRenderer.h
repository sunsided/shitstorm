/** 
 * Project Vector
 * Debug-Renderer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _PHYSICSDEBUGRENDERER_H
#define _PHYSICSDEBUGRENDERER_H

#include "global.h"
#include "IrrBtConversion.h"
#include <iostream>

namespace pv {
namespace physics {

	//! Klasse, die die Physikengine darstellt
	class PhysicsDebugRenderer : public btIDebugDraw
	{
	public:

		//! Erzeugt eine neue Instanz des Objektes
		PhysicsDebugRenderer(irr::video::IVideoDriver* driver) : driver(driver)
		{
			ASSERT(driver);

			// Materialien erzeugen
			material.Lighting = false;
			material.Thickness = 2.0f;
			material.Wireframe = true;
			material.FrontfaceCulling = false;
			material.BackfaceCulling = false;
		}

		//! Destruktor
		virtual ~PhysicsDebugRenderer(void) {}

		//! Bereitet das Zeichnen vor
		void prepareDrawing() {
			driver->setMaterial(material);
			irr::core::matrix4 m; m.makeIdentity();
			driver->setTransform(irr::video::ETS_WORLD, m);
		}

		inline void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
			driver->draw3DLine(conversion::toIrrlichtVector(from), conversion::toIrrlichtVector(to), irr::video::SColorf(color.x(), color.y(), color.z()).toSColor());
		}

		inline void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) {
		}

		inline void reportErrorWarning(const char* warningString) {
			std::wcerr << warningString << std::endl;
		}

		inline void draw3dText(const btVector3& location,const char* textString) {
		}

		//! Setzt den Debug-Modus
		inline void setDebugMode(int debugMode) { mode = debugMode; }
	
		//! Ermittelt den Debug-Modus
		inline int getDebugMode() const { return mode; }

	private:
		
		//! Der Szenenmanager
		irr::video::IVideoDriver* driver;

		//! Der Debug-Modus
		int mode;

		//! Das verwendete Material
		irr::video::SMaterial material;
	};

}}

#endif
