/** 
 * Project Vector
 * SceneNode, der eine Ebene zur Verfügung stellt
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#include "PlaneSceneNode.h"

namespace pv {
namespace nodes
{

	//! Erzeugt eine neue Instanz der PlaneSceneNode-Klasse
	void PlaneSceneNode::initPlane(f32 width, f32 height, u8 quadsW, u8 quadsH, f32 uStart, f32 uEnd, f32 vStart, f32 vEnd) 
	{
		// Fehler beheben
		if(quadsW<1) quadsW = 1;
		if(quadsH<1) quadsH = 1;
		
		// Platz besorgen
		u8 countW = 2+(quadsW-1);
		u8 countH = 2+(quadsH-1);
		VertexCount = countW*countH;
		scene::SMeshBuffer *MeshBuffer = new scene::SMeshBuffer();

		// Vertexkoordinaten
		f32 xStart	= -width/2;
		f32 yStart	= -height/2;
		f32 xStep	=  width/(countW-1);
		f32 yStep	=  height/(countH-1);

		// Texturkoordinaten
		f32 uStep	= (uEnd-uStart)/(countW-1);
		f32 vStep	= (vEnd-vStart)/(countH-1);

		// Zu verwendende Vertexfarbe
		video::SColor white = video::SColor(255, 255,255,255);

		// Punkte generieren
		for(u8 y=0; y<countH; ++y)
		{
			f32 vertexY = yStart + y*yStep;
			f32 vertexV = vStart + y*vStep;
			for(u8 x=0; x<countW; ++x)
			{
				int vertexIndex = y*countW + x;

				f32 vertexX = xStart + x*xStep;
				f32 vertexU = uStart + x*uStep;
				video::S3DVertex *vertex = &irr::video::S3DVertex( vertexX, 0, vertexY, 0,1,0, white, vertexU, vertexV);
				video::S3DVertexTangents foo;
				MeshBuffer->Vertices.push_back(*vertex);

				// Bounding Box generieren
				if(vertexIndex > 0) Box.addInternalPoint(vertex->Pos);
				else Box.reset(vertex->Pos);
			}
		}

		// Platz für die Indizes schaffen
		TriangleCount = quadsW*quadsH*2;
		int indexCount = TriangleCount*3;

		// Indizes neu ermitteln; Alle Quadrate durchlaufen
		for(int squareY=0; squareY<quadsH; ++squareY) 
		{
			u16 squareRowStartIndex = squareY*quadsW + squareY%quadsH;
			for(int squareX=0; squareX<quadsW; ++squareX) 
			{
				u16 topLeft		= squareRowStartIndex + squareX;
				u16 bottomLeft	= topLeft + quadsW+1;

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
		{
			scene::SMesh mesh;
			mesh.addMeshBuffer(MeshBuffer);

			// Mesh neuberechnen
			Mesh = SceneManager->getMeshManipulator()->createMeshWithTangents(&mesh);
		}

		// Material setzen
		Material.Wireframe = false;
		Material.Lighting = true;
		Material.MaterialType = video::EMT_SOLID;
		Material.BackfaceCulling = true;
	}

	//! Destruktor
	PlaneSceneNode::~PlaneSceneNode(void) {
	}

	//! Rendert den Knoten
	void PlaneSceneNode::render() {
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawMeshBuffer(Mesh->getMeshBuffer(0));
	}

	//! Reagiert auf das RegisterSceneNode-Ereignis
	void PlaneSceneNode::OnRegisterSceneNode() {
		if (!isVisible()) return;

		SceneManager->registerNodeForRendering(this);
		ISceneNode::OnRegisterSceneNode();
	}

}}