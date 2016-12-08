#ifndef TEXTURE_DX_H_
#define TEXTURE_DX_H_
#include "Texture.h"
#include <d3d11.h>
#include "GAPIContextLocator.h"

class Texture_DX : public Texture, protected GAPIContextLocator {
private:
	ID3D11ShaderResourceView* _shaderResourceView;

public:
	Texture_DX() = default;
	~Texture_DX();

	bool Load(const std::wstring& fileName) override;

	ID3D11ShaderResourceView* GetShaderResourceView() const noexcept { return _shaderResourceView; }
};

#endif //TEXTURE_DX_H_
