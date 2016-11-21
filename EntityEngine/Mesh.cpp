#include "Mesh.h"
#if BUILD_DIRECTX
#include "VBO_DX.h"
#endif
#if BUILD_OPENGL
#include "VBO_GL.h"
#endif
#include "Vector4.h"
#include <fstream>
#include "IBO_DX.h"
using namespace std;

/******************************************************************************************************************/

Mesh::Mesh()
	:	_locked(false),
		_vbo(nullptr),
		_ibo(nullptr)
	
{
}

/******************************************************************************************************************/

Mesh::~Mesh()
{
	delete _vbo;
	_vbo = nullptr;

	delete _ibo;
	_ibo = nullptr;
}

/******************************************************************************************************************/

void Mesh::SetVertexData(Vertex *verts, int count)
{
	_vertices.resize(count);
	memcpy(_vertices.data(), verts, sizeof(Vertex) * count);
}

bool Mesh::AddVertex(Vertex v)
{
	if (!_locked)
	{
		_vertices.push_back(v);
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************************************************/

bool Mesh::DeleteVertex(int i)
{
	if (!_locked)
	{
		_vertices.erase(_vertices.begin() + i);
		return true;
	}
	
	return false;
}

/******************************************************************************************************************/

bool Mesh::Clear()
{
	if (!_locked)
	{
		_vertices.clear();
		return true;
	}
	return false;
}

/******************************************************************************************************************/

void Mesh::Reset()
{
	delete _vbo;
	_vbo = nullptr;
	_locked = false;
}

/******************************************************************************************************************/

void Mesh::CreateBuffers(Renderer* renderer)
{
	_locked = true;

#if BUILD_DIRECTX
	_vbo = new VBO_DX;
	if (_indices.size()) {
		_ibo = new IBO_DX;
	}
#else
	_vbo = new VBO_GL();
	if (_indices.size()) {
		_ibo = new IBO_GL;
	}
#endif

	_vbo->Create(renderer, _vertices.data(), NumVertices());

	if (_ibo) {
		_ibo->Create(renderer, _indices.data(), NumIndices());
	}
}

/******************************************************************************************************************/

float Mesh::CalculateMaxSize()
{
	float max = 0;
	for (int i = 0; i < NumVertices(); i++)
	{
		Vertex& v = _vertices[i];
		Vector4 vec(v.x, v.y, v.z, 1);
		float dist = vec.lengthSquared();
		if (dist > max)
		{
			max = dist;
		}
	}
	return sqrt(max);
}


void Mesh::GenerateIndices()
{
	int quad_count = _vertices.size() / 4;
	int triangle_count = quad_count * 2;

	_indices.resize(triangle_count * 3);

	for (int i = 0, j = 0; i < _indices.size(); i += 6, j +=4) {
		_indices[i] = j;
		_indices[i + 1] = _indices[i + 4] = j + 1;
		_indices[i + 2] = _indices[i + 3] = j + 2;
		_indices[i + 5] = j + 3;
	}
}

/******************************************************************************************************************/

bool Mesh::LoadFromFile(std::string filename)
{
	ifstream in(filename);
	if (in)
	{
		int numVertices;
		in >> numVertices;
		for (int i = 0; i < numVertices; i++)
		{
			Vertex v;
			in >> v.x;
			in >> v.y;
			in >> v.z;
			in >> v.r;
			in >> v.g;
			in >> v.b;
			in >> v.a;
			AddVertex(v);
		}
		return true;
	}
	else
	{
		// Could not open file
		return false;
	}
}

/******************************************************************************************************************/

bool Mesh::LoadFromStream(std::ifstream& in)
{
	int numVertices;
	in >> numVertices;
	for (int i = 0; i < numVertices; i++)
	{
		Vertex v;
		in >> v.x;
		in >> v.y;
		in >> v.z;
		in >> v.r;
		in >> v.g;
		in >> v.b;
		in >> v.a;
		AddVertex(v);
	}
	return true;
}

/******************************************************************************************************************/
