#include "CubeNode.h"
using namespace video;

void CubeNode::initCube(f32 width, f32 height, f32 depth) 
{
	Material.Wireframe = false;
	Material.Lighting = true;
	Material.MaterialType = E_MATERIAL_TYPE::EMT_SOLID;
	Material.ColorMaterial = E_COLOR_MATERIAL::ECM_AMBIENT; // Vertexfarben sind Ambiente Farben
	Material.BackfaceCulling = true;

	// Alphawert
	u32 alpha = 255;

	// Punkte definieren: Boden
	Vertices[0] = irr::video::S3DVertex( -width/2,-height / 2,-depth/2, 1,1,0, SColor(alpha,0,255,255), 0, 1);
	Vertices[1] = irr::video::S3DVertex(  width/2,-height / 2,-depth/2, 1,0,0, SColor(alpha,255,0,255), 1, 1);
	Vertices[2] = irr::video::S3DVertex(  width/2,-height / 2, depth/2, 0,1,1, SColor(alpha,255,255,0), 1, 0);
	Vertices[3] = irr::video::S3DVertex( -width/2,-height / 2, depth/2, 0,0,1, SColor(alpha,0,255,0), 0, 0);
	// Punkte definieren: Decke
	Vertices[4] = irr::video::S3DVertex( -width/2, height / 2,-depth/2, 0,0,1, SColor(alpha,0,0,255), 0, 0);
	Vertices[5] = irr::video::S3DVertex(  width/2, height / 2,-depth/2, 0,0,1, SColor(alpha,255,0,0), 0, 0);
	Vertices[6] = irr::video::S3DVertex(  width/2, height / 2, depth/2, 0,0,1, SColor(alpha,0,0,0), 0, 0);
	Vertices[7] = irr::video::S3DVertex( -width/2, height / 2, depth/2, 0,0,1, SColor(alpha,255,255,255), 0, 0);

	// Bounding Box bauen
	Box.reset(Vertices[0].Pos); 
	for (s32 i=1; i<8; ++i)
	{
		Box.addInternalPoint(Vertices[i].Pos);
	}
}

CubeNode::~CubeNode(void)
{
}

void CubeNode::render() 
{
	// Die Reihenfolge, in der die Indizes abgearbeitet werden sollen
	irr::u16 indices[] = 
		{0,1,2,
		0,2,3,
		1,6,2,
		1,5,6,
		0,5,1,
		0,4,5,
		0,3,7,
		0,7,4,
		2,7,3,
		2,6,7,
		4,6,5,
		4,7,6 };

	IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(E_TRANSFORMATION_STATE::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&Vertices[0], 8, &indices[0], 12);
}