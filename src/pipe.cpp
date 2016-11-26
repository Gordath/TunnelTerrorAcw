#include "pipe.h"
#include "RenderComponent.h"
#include <GL/GLM/gtc/constants.inl>

void Pipe::CreateFirstRing(float u, Vertex *vertArr) const
{
	float vStep = (2.0f * glm::pi<float>()) / _pipeSegments;

	glm::vec3 posA = GetPointOnTorus(0.0f, 0.0f);
	glm::vec3 posB = GetPointOnTorus(u, 0.0f);

	Vertex vertexA{ posA, glm::vec4{fabs(sin(u)), fabs(cos(u)), 1.0f, 1.0f} };
	Vertex vertexB{ posB, glm::vec4{fabs(sin(u)), fabs(cos(u)), 1.0f, 1.0f} };

	for (int v = 1, i = 0; v <= _pipeSegments; v++, i += 4) {
		vertArr[i] = vertexA;

		glm::vec3 tmpPos{ GetPointOnTorus(0.0f, v * vStep) };
		Vertex tmpVert{ tmpPos, glm::vec4{1.0f, fabs(cos(u)), 1.0f, 1.0f} };
		
		vertArr[i + 1] = vertexA = tmpVert;
		vertArr[i + 2] = vertexB;

		posA = GetPointOnTorus(u, v * vStep);
		tmpVert = Vertex{ posA, {1.0f, fabs(cos(u)), 1.0f, 1.0f} };

		vertArr[i + 3] = vertexB = tmpVert;
	}
}

void Pipe::CreateRing(float u, int i, Vertex* vertArr) const
{
	float vStep = (2.0f * glm::pi<float>()) / _pipeSegments;
	int ringOffset = _pipeSegments * 4;

	glm::vec3 pos = GetPointOnTorus(u, 0.0f);
	Vertex vertex{ pos, glm::vec4{1.0f, 1.0f - u, 1.0f, 1.0f } };
	for (int v = 1; v <= _pipeSegments; v++, i += 4) {
		vertArr[i] = vertArr[i - ringOffset + 2];
		vertArr[i + 1] = vertArr[i - ringOffset + 3];
		vertArr[i + 2] = vertex;

		pos = GetPointOnTorus(u, v * vStep);

		vertArr[i + 3] = vertex = Vertex{ pos, glm::vec4{1.0f, 1.0f - u, 1.0f, 1.0f} };
	}
}

Mesh* Pipe::GenerateMesh()
{
	int vertCount = _pipeSegments * _curveSegments * 4;
	Vertex *vertices = new Vertex[vertCount];

	float uStep = (2.0f * glm::pi<float>()) / _curveSegments * _curveDistance;
	_eulerAngles.z = - uStep * _curveSegments;
	CreateFirstRing(uStep, vertices);

	int iDelta = _pipeSegments * 4;
	for (int u = 2, i = iDelta; u <= _curveSegments; u++, i += iDelta) {
		CreateRing(u * uStep, i, vertices);
	}

	Mesh *m{ new Mesh };

	m->SetVertexData(vertices, vertCount);

	delete[] vertices;

	m->GenerateIndices(VertexWinding::ANTICLOCKWISE);

	return m;
}

//Temporary hack to check if the torus works. Remove the renderer from here. The mesh generation will happen in the pipe system class.
Pipe::Pipe(float curveRadius, float pipeRadius, float curveSegments, float pipeSegments, Renderer* renderer) : GameObject("pipe"),
                                                                                           _curveRadius(curveRadius),
                                                                                           _pipeRadius(pipeRadius),
                                                                                           _curveSegments(curveSegments),
                                                                                           _pipeSegments(pipeSegments)
{
	
	Mesh* m = GenerateMesh();

	m->CreateBuffers(renderer);

	RenderComponent* rc{ new RenderComponent(this) };
	rc->SetMesh(m);
}

glm::vec3 Pipe::GetPointOnTorus(float u, float v) const
{
	float r = _curveRadius + _pipeRadius * cos(v);
	return glm::vec3{r * sin(u), r * cos(u), _pipeRadius * sin(v)};
}

glm::vec3 Pipe::GetPointOnCurve(float u) const
{
	return glm::vec3{ _curveRadius * sin(u), _curveRadius * cos(u), 0.0f };
}
