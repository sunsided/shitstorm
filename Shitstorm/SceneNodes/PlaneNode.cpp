#include "PlaneNode.h"


void PlaneNode::initPlane(f32 width, f32 height, u8 quads, f32 uStart, f32 uEnd, f32 vStart, f32 vEnd) 
{
	// Fehler beheben
	if(quads<1) quads = 1;

	// Aufräumen
	this->quads = quads;

	// Platz besorgen
	u8 count = 2+(quads-1);
	VertexCount = count*count;
	SMeshBuffer *MeshBuffer = new SMeshBuffer();

	// Vertexkoordinaten
	f32 xStart	= -width/2;
	f32 yStart	= -height/2;
	f32 xStep	=  width/(count-1);
	f32 yStep	=  height/(count-1);

	// Texturkoordinaten
	f32 uStep	= (uEnd-uStart)/(count-1);
	f32 vStep	= (vEnd-vStart)/(count-1);

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
			S3DVertex *vertex = &irr::video::S3DVertex( vertexX, 0, vertexY, 0,1,0, white, vertexU, vertexV);
			S3DVertexTangents foo;
			MeshBuffer->Vertices.push_back(*vertex);

			// Bounding Box generieren
			if(vertexIndex > 0) Box.addInternalPoint(vertex->Pos);
			else Box.reset(vertex->Pos);

			// Nächster Vertexindex
			++vertexIndex;
		}
	}

	// Platz für die Indizes schaffen
	TriangleCount = quads*quads*2;
	int indexCount = TriangleCount*3;

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
			MeshBuffer->Indices.push_back(topLeft);
			MeshBuffer->Indices.push_back(bottomLeft);
			MeshBuffer->Indices.push_back(topRight);

			// Zweites Dreieck
			MeshBuffer->Indices.push_back(topRight);
			MeshBuffer->Indices.push_back(bottomLeft);
			MeshBuffer->Indices.push_back(bottomRight);
		}
	}

	// Temporäres Mesh generieren
	SMesh *mesh = new SMesh();
	mesh->addMeshBuffer(MeshBuffer);

	// Mesh neuberechnen
	Mesh = SceneManager->getMeshManipulator()->createMeshWithTangents(mesh);

	// Temporäres Mesh entfernen
	delete(mesh);

	// Material setzen
	Material.Wireframe = false;
	Material.Lighting = true;
	Material.MaterialType = EMT_SOLID;
	Material.BackfaceCulling = true;
}

PlaneNode::~PlaneNode(void)
{
}

void PlaneNode::render() 
{
	IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(ETS_WORLD, AbsoluteTransformation);
	//driver->drawIndexedTriangleList(&Vertices[0], VertexCount, &Indices[0], TriangleCount);
	driver->drawMeshBuffer(Mesh->getMeshBuffer(0));
}

void PlaneNode::OnRegisterSceneNode() 
{
	SceneManager->registerNodeForRendering(this);
	ISceneNode::OnRegisterSceneNode();
}