#pragma once
#include <map>
#include <string>
#include <vector>
#include "Mesh.h"

typedef std::map<std::string, Mesh*>::iterator MeshIterator;

class MultiMesh {
private:
	std::map<std::string, Mesh*> _meshes;

public:
	MultiMesh();
	~MultiMesh();

	Mesh* GetMesh(std::string key) const;

	int NumMeshes() const { return static_cast<int>(_meshes.size()); }

	void CreateVBOs(Renderer* r);

	void Clear();

	// Loads the Mesh from a file (returns true if loaded OK)
	bool LoadFromFile(std::string filename);

	// Unlocks the mesh but also deletes the VBO
	void Reset();
};
