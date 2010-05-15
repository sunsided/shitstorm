#include "PlaneNode.h"


void PlaneNode::initPlane(f32 width, f32 height) 
{
	Material.Wireframe = false;
	Material.Lighting = true;
	Material.MaterialType = E_MATERIAL_TYPE::EMT_SOLID;
	Material.BackfaceCulling = true;

	// Punkte definieren
	SColor white = SColor(255,  255,255,255);
	Vertices[0] = irr::video::S3DVertex( -width/2,  0, height/2, 0,1,0,		white, 0, 0);
	Vertices[1] = irr::video::S3DVertex(  width/2,  0, height/2, 0,1,0,		white, 1, 0);
	Vertices[2] = irr::video::S3DVertex( -width/2,  0, -height/2, 0,1,0,	white, 0, 1);
	Vertices[3] = irr::video::S3DVertex(  width/2,  0, -height/2, 0,1,0,	white, 1, 1);

	// Bounding Box bauen
	Box.reset(Vertices[0].Pos); 
	for (s32 i=1; i<3; ++i)
	{
		Box.addInternalPoint(Vertices[i].Pos);
	}
}

PlaneNode::~PlaneNode(void)
{
}

void PlaneNode::render() 
{
	// Die Reihenfolge, in der die Indizes abgearbeitet werden sollen
	irr::u16 indices[] = 
		{0,1,2,
		2,1,3};

	IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(E_TRANSFORMATION_STATE::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&Vertices[0], 4, &indices[0], 2);
}