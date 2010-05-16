#include "PlaneNode.h"


void PlaneNode::initPlane(f32 width, f32 height, u8 quads) 
{
	// Aufräumen
	if(Vertices) free(Vertices);
	if(Indices) free(Indices);
	this->quads = quads;

	// Platz besorgen
	u8 count = 2+(quads-1);
	VertexCount = count*count;
	Vertices = (video::S3DVertex*)malloc(VertexCount * sizeof(video::S3DVertex));

	// Vertexkoordinaten
	f32 xStart	= -width/2;
	f32 yStart	= -height/2;
	f32 xStep	=  width/(count-1);
	f32 yStep	=  height/(count-1);

	// Texturkoordinaten
	f32 uStart	= 0;
	f32 vStart	= 0;
	f32 uStep	= 1.0F/(count-1);
	f32 vStep	= 1.0F/(count-1);

	// Zu verwendende Vertexfarbe
	SColor white = SColor(255, 255,255,255);

	// Punkte generieren
	int vertexIndex = 0;
	for(u8 y=0; y<count; ++y)
	{
		f32 vertexY = yStart + y*yStep;
		f32 vertexV = vStart + y*vStep;
		for(u8 x=0; x<count; ++x)
		{
			f32 vertexX = xStart + x*xStep;
			f32 vertexU = uStart + x*uStep;
			Vertices[vertexIndex] = irr::video::S3DVertex( vertexX, 0, vertexY, 0,1,0, white, vertexU, vertexV);

			// Bounding Box generieren
			if(vertexIndex > 0) Box.addInternalPoint(Vertices[vertexIndex].Pos);
			else Box.reset(Vertices[vertexIndex].Pos);

			// Nächster Vertexindex
			++vertexIndex;
		}
	}

	// Platz für die Indizes schaffen
	TriangleCount = quads*quads*2;
	int indexCount = TriangleCount*3;
	Indices = (u16*)malloc(indexCount*sizeof(u16));

	// Indizes neu ermitteln; Alle Quadrate durchlaufen
	vertexIndex = 0;
	for(int squareY=0; squareY<this->quads; ++squareY) 
	{
		u16 squareRowStartIndex = squareY*this->quads + squareY%this->quads;
		for(int squareX=0; squareX<this->quads; ++squareX) 
		{
			u16 topLeft		= squareRowStartIndex + squareX;
			u16 bottomLeft	= topLeft + this->quads+1;

			u16 topRight	= topLeft + 1;
			u16 bottomRight	= bottomLeft + 1;

			// Erstes Dreieck
			Indices[vertexIndex++] = topLeft;
			Indices[vertexIndex++] = bottomLeft;
			Indices[vertexIndex++] = topRight;

			// Zweites Dreieck
			Indices[vertexIndex++] = topRight;
			Indices[vertexIndex++] = bottomLeft;
			Indices[vertexIndex++] = bottomRight;
		}
	}

	// Material setzen
	Material.Wireframe = false;
	Material.Lighting = true;
	Material.MaterialType = E_MATERIAL_TYPE::EMT_SOLID;
	Material.BackfaceCulling = true;
}

PlaneNode::~PlaneNode(void)
{
	if(Vertices) free(Vertices);
	if(Indices) free(Indices);
}

void PlaneNode::render() 
{
	// Die Reihenfolge, in der die Indizes abgearbeitet werden sollen
	/*
	irr::u16 indices[] = 
		{0,2,1,
		1,2,3};
	*/

	IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(E_TRANSFORMATION_STATE::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(&Vertices[0], VertexCount, &Indices[0], TriangleCount);
}