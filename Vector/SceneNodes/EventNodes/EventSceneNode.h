/** 
 * Project Vector
 * Event-Szenenknoten ("Trigger")
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#pragma once
#ifndef _EVENTSCENENODE_H
#define _EVENTSCENENODE_H

#include "global.h"
#include "Events/EventTriggeringObject.h"
using namespace irr;

namespace pv {
namespace nodes {
namespace eventnodes {

	//! Event-Szenenknoten ("Trigger")
	class EventSceneNode : public scene::ISceneNode
	{
	public:
		//! Erzeugt eine neue Instanz der OrientationHelperSceneNode-Klasse
		EventSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id = -1);
		
		//! Destruktor
		virtual ~EventSceneNode(void) {}

		//! Tritt auf, wenn ein Objekt das Triggerfeld betritt
		virtual void OnEnter(events::EventTriggeringObject* object) {}

		//! Tritt auf, wenn der Objekt das Triggerfeld verlässt 
		virtual void OnExit(events::EventTriggeringObject* object) {}
	};

}}}

#endif