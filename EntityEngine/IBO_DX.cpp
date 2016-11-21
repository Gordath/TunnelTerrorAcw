#include "IBO_DX.h"
#include <minwinbase.h>
#include "Renderer_DX.h"


IBO_DX::~IBO_DX()
{
	if(_ibo) {
		_ibo->Release();
	}
}

void IBO_DX::Create(Renderer* renderer, unsigned int indices[], int numIndices)
{
	_numIndices = numIndices;

	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));

	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	buffer_desc.ByteWidth = sizeof(unsigned int) * numIndices;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Renderer_DX* rendererDX = static_cast<Renderer_DX*>(renderer);
	rendererDX->GetDevice()->CreateBuffer(&buffer_desc, nullptr, &_ibo);

	D3D11_MAPPED_SUBRESOURCE index_data;
	ZeroMemory(&index_data, sizeof(index_data));

	rendererDX->GetContext()->Map(_ibo, 0, D3D11_MAP_WRITE_DISCARD, 0, &index_data);
	memcpy(index_data.pData, indices, sizeof(unsigned int) * numIndices);
	rendererDX->GetContext()->Unmap(_ibo, 0);
}

void IBO_DX::Bind(Renderer* renderer)
{
	Renderer_DX* rendererDx = static_cast<Renderer_DX*>(renderer);

	rendererDx->GetContext()->IASetIndexBuffer(_ibo, DXGI_FORMAT_R32_UINT, 0);
}

void IBO_DX::Draw(Renderer* renderer)
{
	Renderer_DX* rendererDx = static_cast<Renderer_DX*>(renderer);

	rendererDx->GetContext()->DrawIndexed(_numIndices, 0, 0);
}
