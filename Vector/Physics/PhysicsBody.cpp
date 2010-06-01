/** 
 * Project Vector
 * Physikkörper
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PhysicsBody.h"
#include "PhysicsWorld.h"

// 360 / (2*PI)
#ifndef GRAD_PI 
#define GRAD_PI 57.29577951f
#endif

#ifndef GRAD_PI2
#define GRAD_PI2 0.0174532925f
#endif

namespace pv {
namespace physics {

	//! Destruktor
	PhysicsBody::~PhysicsBody(void) {
		endPhysics();
	}

	//! Wandelt einen Quaternion in einen Euler-Rotationsvektor um
	void PhysicsBody::QuaternionToEulerXYZ(const btQuaternion &quat,btVector3 &euler) {
		f32 w = quat.getW();	
		f32 x = quat.getX();	
		f32 y = quat.getY();	
		f32 z = quat.getZ();

		float sqw = w*w;
		float sqx = x*x;
		float sqy = y*y;
		float sqz = z*z;

		euler.setZ((atan2(2.0f * (x*y + z*w),(sqx - sqy - sqz + sqw))));
		euler.setX((atan2(2.0f * (y*z + x*w),(-sqx - sqy + sqz + sqw))));
		euler.setY((asin(-2.0f * (x*z - y*w))));
	}

	//! Wandelt einen Euler-Rotationsvektor in einen Quaternion um
	void PhysicsBody::EulerXYZToQuaternion(btVector3 &euler, btQuaternion &quat) {	

		btMatrix3x3 mat;
		mat.setIdentity();
		mat.setEulerZYX(euler.getX(), euler.getY(), euler.getZ());
		mat.getRotation(quat);
	}

	//get mesh data. Bullet can use the meshbuffer data directly in btTriangleIndexVertexArray,
	// but Irrlicht indices are 16 bits wide which is not compatible with Bullet :(
	//So we are just using a btTriangleMesh instead, although it would probably
	// be faster to store the indices in int arrays and use these in a btTriangleIndexVertexArray
	btTriangleMesh* PhysicsBody::GetTriangleMesh(scene::IMesh* pMesh)
	{	
		btVector3 vertices[3];
		u32 i,j,k,index,numVertices;
		u16* mb_indices;

		btTriangleMesh *pTriMesh = new btTriangleMesh();
		for(i=0; i<pMesh->getMeshBufferCount(); i++) {

			irr::scene::IMeshBuffer* mb = pMesh->getMeshBuffer(i);

			//extract vertex data
			//because the vertices are stored as structs with no common base class,
			// we need to handle each type separately
			if (mb->getVertexType() == irr::video::EVT_STANDARD) {

				irr::video::S3DVertex* mb_vertices = (irr::video::S3DVertex*)mb->getVertices();
				mb_indices = mb->getIndices();
				numVertices = mb->getVertexCount();
				
				for (j=0; j<mb->getIndexCount();j+=3) { //get index into vertex list
					for (k=0; k<3; ++k) { //three verts per triangle
						index = mb_indices[j+k];
						if (index > numVertices) goto error;
						//convert to btVector3
						vertices[k] = btVector3(mb_vertices[index].Pos.X,mb_vertices[index].Pos.Y,mb_vertices[index].Pos.Z);		
					}
					pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
				}
			
			}
			else if (mb->getVertexType() == irr::video::EVT_2TCOORDS) {

				//same but for S3DVertex2TCoords data
				irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)mb->getVertices();
				u16* mb_indices = mb->getIndices();
				s32 numVertices = mb->getVertexCount();

				for(j=0; j<mb->getIndexCount(); j+=3){ //index into irrlicht data
					for (k=0; k<3; ++k) {
						s32 index = mb_indices[j+k];
						if (index > numVertices) goto error;
						vertices[k] = btVector3(mb_vertices[index].Pos.X,mb_vertices[index].Pos.Y,mb_vertices[index].Pos.Z);		
					}
					pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
				}
			}	
			//not bothering with EVT_TANGENTS vertex type
		}

		return pTriMesh;

	error:
		//should have better error handling than this
		delete pTriMesh;
		return 0;
	}

}}
