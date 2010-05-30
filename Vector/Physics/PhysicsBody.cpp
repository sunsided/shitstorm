/** 
 * Project Vector
 * Physikkörper
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsBody.h"

using namespace bullet;

namespace pv {
namespace physics {
	
	//! Konstruktor
	PhysicsBody::PhysicsBody(void) 
		: motionState(NULL)
	{}

	//! Destruktor
	PhysicsBody::~PhysicsBody(void) {}

}}
