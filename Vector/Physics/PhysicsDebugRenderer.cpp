/** 
 * Project Vector
 * Debug-Renderer
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsDebugRenderer.h"

using namespace irr;
using namespace irr::core;
using namespace irr::video;

namespace pv {
namespace physics {
	
	void PhysicsDebugRenderer::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) {
		
		const f32 pointSize = 0.1f;

		vector3df center(PointOnB.x(), PointOnB.y(), PointOnB.z());
		vector3df size(pointSize, pointSize, pointSize);
		aabbox3df box(center - size, center + size);

		SColorf vcolor(1.0f, color.x(), color.y(), color.z());
		driver->draw3DBox(box, vcolor.toSColor());
	}

}}
