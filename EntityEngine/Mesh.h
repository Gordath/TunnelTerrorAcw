#pragma once
#include <vector>
#include "VBO.h"
#include "Vertex.h"
#include "IBO.h"
#include "Resource.h"

class Renderer;

enum class VertexWinding {
	CLOCKWISE,
	ANTICLOCKWISE
};

class Mesh : public Resource {
private:
	bool _locked; // True once we've made the VBO; can no longer add vertices etc unless reset
	VBO* _vbo;
	IBO* _ibo;
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;

public:
	Mesh();
	~Mesh();

	VBO* GetVBO() const { return _vbo; }
	IBO* GetIBO() const { return _ibo; }
	int NumVertices() const { return static_cast<int>(_vertices.size()); }
	int NumIndices() const { return static_cast<int>(_indices.size()); }
	Vertex GetVertex(int i) const { return _vertices[i]; }
	Vertex& GetVertexRef(int i) { return _vertices[i]; }

	void SetVertexData(Vertex* verts, int count);

	void CreateBuffers(Renderer* r);
	bool AddVertex(Vertex v);
	bool Clear();
	bool DeleteVertex(int i);

	bool Load(const std::wstring& fileName) override;

	// Unlocks the mesh but also deletes the VBO
	void Reset();

	// Calculates max size of mesh in any direction
	float CalculateMaxSize();

	void GenerateIndices(VertexWinding winding);
};
