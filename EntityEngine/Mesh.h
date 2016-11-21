#pragma once
#include <vector>
#include "VBO.h"
#include "Vertex.h"
#include "IBO.h"

class Renderer;

enum class MeshDrawMode {
	MESH_DRAW,
	MESH_DRAW_INDEXED
};

class Mesh
{
	// Data
private:
	bool _locked;	// True once we've made the VBO; can no longer add vertices etc unless reset
	VBO* _vbo;
	IBO* _ibo;
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;

	// Constructors etc
public:
	Mesh();
	~Mesh();

	// Gets/sets
public:
	VBO* GetVBO()			const	{ return _vbo; }
	IBO* GetIBO()			const	{ return _ibo; }
	int NumVertices()		const	{ return static_cast<int>(_vertices.size()); }
	int NumIndices()		const	{ return static_cast<int>(_indices.size()); }
	Vertex GetVertex(int i)	const	{ return _vertices[i]; }
	Vertex& GetVertexRef(int i)		{ return _vertices[i]; }

	// Functions
public:
	void CreateBuffers(Renderer* r)				;
	bool AddVertex(Vertex v)					;
	bool Clear()								;
	bool DeleteVertex(int i)					;
	
	// Loads the Mesh from a file (returns true if loaded OK)
	bool LoadFromFile(std::string filename)		;

	// Loads the Mesh from an existing stream (returns true if OK)
	bool Mesh::LoadFromStream(std::ifstream& in);

	// Unlocks the mesh but also deletes the VBO
	void Reset()								;

	// Calculates max size of mesh in any direction
	float CalculateMaxSize()					;

	void GenerateIndices();
};

