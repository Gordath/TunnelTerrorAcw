#include "Texture_DX.h"
#include <d3dx11tex.h>
#include "Context_DX.h"


Texture_DX::~Texture_DX()
{
	_shaderResourceView->Release();
}

bool Texture_DX::Load(const std::wstring& fileName)
{
	ID3D11Device* _dev{ static_cast<Context_DX*>(GetGAPIContext())->GetDevice() };
	HRESULT res{ D3DX11CreateShaderResourceViewFromFile(_dev, fileName.c_str(), nullptr, nullptr, &_shaderResourceView, nullptr) };
	return true;
}
