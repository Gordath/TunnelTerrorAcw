#include "Mesh.h"
#if BUILD_DIRECTX
#include "VBO_DX.h"
#endif
#if BUILD_OPENGL
#include "VBO_GL.h"
#endif

#include "IBO_DX.h"
#include <iostream>
#include <locale>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

using namespace std;

/******************************************************************************************************************/

Mesh::Mesh()
	: _locked(false),
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

void Mesh::SetVertexData(Vertex* verts, int count)
{
	_vertices.resize(count);
	memcpy(_vertices.data(), verts, sizeof(Vertex) * count);
}

bool Mesh::AddVertex(Vertex v)
{
	if (!_locked) {
		_vertices.push_back(v);
		return true;
	}
	else {
		return false;
	}
}

bool Mesh::DeleteVertex(int i)
{
	if (!_locked) {
		_vertices.erase(_vertices.begin() + i);
		return true;
	}

	return false;
}

bool Mesh::Clear()
{
	if (!_locked) {
		_vertices.clear();
		return true;
	}
	return false;
}

bool Mesh::Load(const std::wstring& fileName)
{
	char buff[256];
	int count = 0;
	wcstombs(buff, fileName.c_str(), 256);

	Assimp::Importer importer;
	const aiScene* scene{ importer.ReadFile(buff, aiProcess_CalcTangentSpace |
	                                        aiProcess_Triangulate |
	                                        aiProcess_JoinIdenticalVertices |
	                                        aiProcess_SortByPType) };
	if (!scene) {
		std::cerr << importer.GetErrorString() << std::endl;
		return false;
	}

	if (scene->HasMeshes()) {
		aiMesh* mesh{ scene->mMeshes[0] };

		_vertices.resize(mesh->mNumVertices);
		for (int i = 0; i < mesh->mNumVertices; ++i) {
			_vertices[i].position = glm::vec3{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			_vertices[i].normal = glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
			_vertices[i].tangent = glm::vec3{ mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
			_vertices[i].texcoord = glm::vec2{ mesh->mTextureCoords[0][i].x, 1.0f - mesh->mTextureCoords[0][i].y };
		}

		if (mesh->HasFaces()) {
			for (int i = 0; i < mesh->mNumFaces; ++i) {
				const aiFace& Face = mesh->mFaces[i];
				assert(Face.mNumIndices == 3);
				_indices.push_back(Face.mIndices[0]);
				_indices.push_back(Face.mIndices[1]);
				_indices.push_back(Face.mIndices[2]);
			}
		}
	}

	return true;
}

void Mesh::Reset()
{
	delete _vbo;
	_vbo = nullptr;
	_locked = false;
}

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

float Mesh::CalculateMaxSize()
{
	//calc the center of the mesh.
	glm::vec3 accum;
	for (auto v : _vertices) {
		accum += v.position;
	}

	glm::vec3 center{ accum / static_cast<float>(NumVertices()) };

	float max = 0;
	for (int i = 0; i < NumVertices(); i++) {
		Vertex& v = _vertices[i];
		glm::vec3 vec{ v.position - center };
		float dist = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
		if (dist > max) {
			max = dist;
		}
	}
	return sqrt(max);
}


void Mesh::GenerateIndices(VertexWinding winding)
{
	if(_indices.size()) {
		return;
	}

	int quad_count = _vertices.size() / 4;
	int triangle_count = quad_count * 2;

	_indices.resize(triangle_count * 3);

	for (int i = 0, j = 0; i < _indices.size(); i += 6 , j += 4) {
		_indices[i] = j;
		switch (winding) {
		case VertexWinding::CLOCKWISE:
			_indices[i + 1] = _indices[i + 4] = j + 1;
			_indices[i + 2] = _indices[i + 3] = j + 2;
			break;
		case VertexWinding::ANTICLOCKWISE:
			_indices[i + 1] = _indices[i + 4] = j + 2;
			_indices[i + 2] = _indices[i + 3] = j + 1;
			break;
		default:
			break;
		}

		_indices[i + 5] = j + 3;
	}
}
