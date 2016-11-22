#pragma once
#include "Vertex.h"

class Renderer;

// Abstract VBO class
class VBO {
protected:
	int _numVertices;

public:
	VBO() : _numVertices(0)
	{
	}

	virtual ~VBO() = default;

	virtual void Create(Renderer* renderer, Vertex vertices[], int numVertices) = 0;
	virtual void Bind(Renderer* renderer) = 0;
	virtual void Draw(Renderer* renderer) = 0;
};
