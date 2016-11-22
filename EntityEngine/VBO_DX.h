#pragma once
#if BUILD_DIRECTX

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "VBO.h"

// DirectX specific VBO class
class VBO_DX :
		public VBO {
protected:
	ID3D11Buffer* _vbo;

public:
	VBO_DX();
	virtual ~VBO_DX();

	void Create(Renderer* renderer, Vertex vertices[], int numVertices) override;

	void Bind(Renderer* renderer) override;

	void Draw(Renderer* renderer) override;
};

#endif
