#include "pipe.h"
#include "RenderComponent.h"

void Pipe::createFirstRing(float u, Vertex *vertArr) const
{
	float vStep = (2.0f * PI) / _pipeSegments;

	Vector4 posA = getPointOnTorus(0.0f, 0.0f);
	Vector4 posB = getPointOnTorus(u, 0.0f);

	Vertex vertexA{ posA.x(), posA.y(), posA.z(), 1.0f, 1.0f, 1.0f };
	Vertex vertexB{ posB.x(), posB.y(), posB.z(), 1.0f, 1.0f, 1.0f };

	for (int v = 1, i = 0; v <= _pipeSegments; v++, i += 4) {
		vertArr[i] = vertexA;

		Vector4 tmpPos{ getPointOnTorus(0.0f, v * vStep) };
		Vertex tmpVert{ tmpPos.x(), tmpPos.y(), tmpPos.z(), 1.0f, 1.0f, 1.0f };
		
		vertArr[i + 1] = vertexA = tmpVert;
		vertArr[i + 2] = vertexB;

		tmpPos = getPointOnTorus(u, v * vStep);
		tmpVert = Vertex{ tmpPos.x(), tmpPos.y(), tmpPos.z(), 1.0f, 1.0f, 1.0f };

		vertArr[i + 3] = vertexB = tmpVert;
	}
}

void Pipe::createRing(float u, int i, Vertex* vertArr) const
{
	float vStep = (2.0f * PI) / _pipeSegments;
	int ringOffset = _pipeSegments * 4;

	Vector4 pos = getPointOnTorus(u, 0.0f);
	Vertex vertex{ pos.x(), pos.y(), pos.z(), 1.0f, 1.0f, 1.0f };
	for (int v = 1; v <= _pipeSegments; v++, i += 4) {
		vertArr[i] = vertArr[i - ringOffset + 2];
		vertArr[i + 1] = vertArr[i - ringOffset + 3];
		vertArr[i + 2] = vertex;

		pos = getPointOnTorus(u, v * vStep);

		vertArr[i + 3] = vertex = Vertex{pos.x(), pos.y(), pos.z(), 1.0f, 1.0f, 1.0f};
	}
}

Mesh* Pipe::generateMesh() const
{
	int vertCount = _pipeSegments * _curveSegments * 4;
	Vertex *vertices = new Vertex[vertCount];

	float uStep = (2.0f * PI) / _curveSegments;
	createFirstRing(uStep, vertices);

	int iDelta = _pipeSegments * 4;
	for (int u = 2, i = iDelta; u <= _curveSegments; u++, i += iDelta) {
		createRing(u * uStep, i, vertices);
	}

	Mesh *m{ new Mesh };

	m->SetVertexData(vertices, vertCount);

	delete[] vertices;

	return m;
}

//Temporary hack to check if the torus works. Remove the renderer from here. The mesh generation will happen in the pipe system class.
Pipe::Pipe(float curveRadius, float pipeRadius, float curveSegments, float pipeSegments, Renderer* renderer) : GameObject("pipe"),
                                                                                           _curveRadius(curveRadius),
                                                                                           _pipeRadius(pipeRadius),
                                                                                           _curveSegments(curveSegments),
                                                                                           _pipeSegments(pipeSegments)
{
	
	Mesh* m = generateMesh();
	m->GenerateIndices();

	m->CreateBuffers(renderer);

	RenderComponent* rc{ new RenderComponent(this) };
	rc->SetMesh(m);
}

Vector4 Pipe::getPointOnTorus(float u, float v) const
{
	float r = _curveRadius + _pipeRadius * cos(v);
	return Vector4{r * sin(u), r * cos(u), _pipeRadius * sin(v)};
}
