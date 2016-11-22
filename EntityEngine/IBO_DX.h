#ifndef IBO_DX_H_
#define IBO_DX_H_

#include "IBO.h"
#include <d3d11.h>

class IBO_DX : public IBO {
protected:
	ID3D11Buffer* _ibo;

	// Structors
public:
	IBO_DX() : _ibo(nullptr)
	{
	}

	~IBO_DX();

	void Create(Renderer* renderer, unsigned int indices[], int numIndices) override;
	void Bind(Renderer* renderer) override;
	void Draw(Renderer* renderer) override;
};

#endif //IBO_DX_H_
