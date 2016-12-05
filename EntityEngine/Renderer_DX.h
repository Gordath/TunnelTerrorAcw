#pragma once
#include <GL/GLM/detail/_vectorize.hpp>
#include <GL/GLM/detail/_vectorize.hpp>
#include "PhysicsComponent.h"
#if BUILD_DIRECTX

#include <d3d11.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include "Renderer.h"
#include "FW1FontWrapper.h"

struct UniformBuffer {
	DirectX::XMFLOAT4X4 MVP;
	DirectX::XMFLOAT4X4 MV;
	DirectX::XMFLOAT4X4 ITMV;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;
	DirectX::XMFLOAT4 Vpos;
	DirectX::XMFLOAT4 Lpos;
};

// DirectX Device & Context
class Renderer_DX : public Renderer {
protected:
	IDXGISwapChain* _swapchain; // the pointer to the swap chain interface
	ID3D11Device* _device; // the pointer to our Direct3D device interface
	ID3D11DeviceContext* _context; // the pointer to our Direct3D device context
	ID3D11RenderTargetView* _backbuffer; // the pointer to our back buffer
	ID3D11DepthStencilView* _depthStencil;
	ID3D11InputLayout* _layout; // the pointer to the input layout
	ID3D11VertexShader* _vertexShader; // the pointer to the vertex shader
	ID3D11PixelShader* _pixelShader; // the pointer to the pixel shader
	ID3D11Buffer* _uniformBuffer; // Stores the MVM and colour

	ID3D11BlendState* _blendStateNoBlend;
	ID3D11DepthStencilState * _depthTestOn;

	IFW1Factory* _factory;
	IFW1FontWrapper* _fontWrapper;

	HWND _hWnd; // Window handle

public:
	Renderer_DX(HWND hWnd);

	virtual ~Renderer_DX();

	ID3D11Device* GetDevice() const { return _device; }

	void SetDevice(ID3D11Device* v) { _device = v; }

	ID3D11DeviceContext* GetContext() const { return _context; }

	void SetContext(ID3D11DeviceContext* v) { _context = v; }

	void ClearScreen() override;

	void Destroy() override;

	void Draw(const Mesh* mesh, glm::mat4 M, glm::mat4 V, glm::mat4 P, const Material& material) override;

	void DrawString(const std::wstring text, float size, float xPos, float yPos, unsigned int colorABGR, TextAlignment textAlignment) override;
	
	void Initialise(int width, int height) override;

	void SwapBuffers() override;

	// Initialise the shaders
	void InitialiseShaders();

};

#endif
