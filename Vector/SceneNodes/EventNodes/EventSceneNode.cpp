/** 
 * Project Vector
 * Event-Szenenknoten ("Trigger")
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "EventSceneNode.h"

using namespace core;

namespace pv {
namespace nodes {
namespace eventnodes
{
	//! Erzeugt eine neue Instanz der EventSceneNode-Klasse
	EventSceneNode::EventSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id)
	{ 
	}

}}}