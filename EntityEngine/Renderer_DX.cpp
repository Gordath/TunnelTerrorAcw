#if BUILD_DIRECTX
#include <d3dx11async.h>
#include "Texture_DX.h"
#include "Window.h"
#include "PhysicsComponent.h"
#include "Material.h"
#include <iostream>
#include "GAPIContextLocator.h"
#include "Context_DX.h"
#include "Renderer_DX.h"
#include "Mesh.h"
#include "GameObject.h"
#include <fstream>

/******************************************************************************************************************/

Renderer_DX::Renderer_DX(HWND hWnd)
	: _hWnd(hWnd)
{
}

/******************************************************************************************************************/

Renderer_DX::~Renderer_DX()
{
}

/******************************************************************************************************************/

void Renderer_DX::ClearScreen()
{
	_context->ClearRenderTargetView(_backbuffer, &_clearColour.x);
	_context->ClearDepthStencilView(_depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

/******************************************************************************************************************/

void Renderer_DX::Destroy()
{
	_swapchain->SetFullscreenState(false, nullptr); // switch to windowed mode

	// close and release all existing COM objects
	_layout->Release();
	_vertexShader->Release();
	_pixelShader->Release();
	_swapchain->Release();
	_backbuffer->Release();
	_depthStencil->Release();
	_device->Release();
	_context->Release();
	_blendStateNoBlend->Release();
	_depthTestOn->Release();
	_fontWrapper->Release();
	_factory->Release();
	_sampleState->Release();

	if (_uniformBuffer) {
		_uniformBuffer->Release();
	}
}

/******************************************************************************************************************/

void Renderer_DX::Draw(const Mesh* mesh, glm::mat4 M, glm::mat4 V, glm::mat4 P, const Material& material)
{
	// set the shader objects
	_context->VSSetShader(_vertexShader, nullptr, 0);
	_context->PSSetShader(_pixelShader, nullptr, 0);
	_context->IASetInputLayout(_layout);

	std::vector<ID3D11ShaderResourceView*> textures;
	if(material.textures[TEX_DIFFUSE]) {
		textures.push_back(static_cast<Texture_DX*>(material.textures[TEX_DIFFUSE])->GetShaderResourceView());
	}

	if (material.textures[TEX_SPECULAR]) {
		textures.push_back(static_cast<Texture_DX*>(material.textures[TEX_SPECULAR])->GetShaderResourceView());
	}

	if (material.textures[TEX_NORMAL]) {
		textures.push_back(static_cast<Texture_DX*>(material.textures[TEX_NORMAL])->GetShaderResourceView());
	}
	
	_context->PSSetShaderResources(0, textures.size(), textures.data());
	_context->PSSetSamplers(0, 1, &_sampleState);


	glm::mat4 MV = glm::transpose(V * M);
	glm::mat4 MVP = glm::transpose(P * V * M);
	glm::mat4 ITMV = glm::transpose(glm::inverse(MV));

	UniformBuffer uniforms;
	memcpy(&uniforms.MVP, &MVP[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.MV, &MV[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.ITMV, &ITMV[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.diffuse, &material.diffuse.data, sizeof(DirectX::XMFLOAT4));
	memcpy(&uniforms.specular, &material.specular.data, sizeof(DirectX::XMFLOAT4));
	uniforms.Vpos = DirectX::XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };
	uniforms.Lpos = DirectX::XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f };

	// Need to update uniform buffer here
	D3D11_MAPPED_SUBRESOURCE ms;
	_context->Map(_uniformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms); // map the buffer
	memcpy(ms.pData, &uniforms, sizeof(UniformBuffer)); // copy the data
	_context->Unmap(_uniformBuffer, 0); // unmap the buffer
	_context->VSSetConstantBuffers(0, 1, &_uniformBuffer);
	_context->PSSetConstantBuffers(0, 1, &_uniformBuffer);

	mesh->GetVBO()->Bind(this);

	//if the mesh has indices bind the IBO and draw indexed
	if (mesh->NumIndices()) {
		mesh->GetIBO()->Bind(this);
		mesh->GetIBO()->Draw(this);
	}
	else { //draw normally
		mesh->GetVBO()->Draw(this);
	}
}

void Renderer_DX::DrawString(const std::wstring text, float size, float xPos, float yPos, unsigned int colorABGR, TextAlignment textAlignment)
{
	_fontWrapper->DrawString(_context,
	                         text.c_str(),
	                         size,
	                         xPos,
	                         yPos,
	                         colorABGR,
	                         static_cast<unsigned int>(textAlignment));

	_context->OMSetDepthStencilState(_depthTestOn, 1);
	_context->OMSetBlendState(_blendStateNoBlend, nullptr, 0xffffffff);
	_context->GSSetShader(nullptr, nullptr, 0);
}

/******************************************************************************************************************/

void Renderer_DX::Initialise(int width, int height)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1; // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color
	scd.BufferDesc.Width = width; // set the back buffer width
	scd.BufferDesc.Height = height; // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how swap chain is to be used
	scd.OutputWindow = _hWnd; // the window to be used
	scd.SampleDesc.Count = 4; // how many multisamples
	scd.Windowed = true; // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching

	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(nullptr,
	                              D3D_DRIVER_TYPE_HARDWARE,
	                              nullptr,
	                              0,
	                              nullptr,
	                              0,
	                              D3D11_SDK_VERSION,
	                              &scd,
	                              &_swapchain,
	                              &_device,
	                              nullptr,
	                              &_context);

	_swapchain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

	// get the address of the back buffer
	ID3D11Texture2D* p_backbuffer;
	_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_backbuffer));

	// use the back buffer address to create the render target
	_device->CreateRenderTargetView(p_backbuffer, nullptr, &_backbuffer);
	p_backbuffer->Release();

	D3D11_TEXTURE2D_DESC depth_attachment_desc;
	ZeroMemory(&depth_attachment_desc, sizeof(depth_attachment_desc));
	depth_attachment_desc.Width = Window::TheWindow->_width;
	depth_attachment_desc.Height = Window::TheWindow->_height;
	depth_attachment_desc.MipLevels = 1;
	depth_attachment_desc.ArraySize = 1;
	depth_attachment_desc.Format = DXGI_FORMAT_D32_FLOAT;
	depth_attachment_desc.SampleDesc.Count = 4;
	depth_attachment_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	HRESULT res{ 0 };
	ID3D11Texture2D* p_depth;
	res = _device->CreateTexture2D(&depth_attachment_desc, nullptr, &p_depth);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	res = _device->CreateDepthStencilView(p_depth, &dsvd, &_depthStencil);
	p_depth->Release();

	// set the render target as the back buffer
	_context->OMSetRenderTargets(1, &_backbuffer, _depthStencil);


	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	_context->RSSetViewports(1, &viewport);

	// Initialise shaders
	InitialiseShaders();

	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.RenderTarget[0].BlendEnable = FALSE;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	_device->CreateBlendState(&BlendState, &_blendStateNoBlend);

	D3D11_DEPTH_STENCIL_DESC dsDesc;

	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	_device->CreateDepthStencilState(&dsDesc, &_depthTestOn);

	FW1CreateFactory(FW1_VERSION, &_factory);
	_factory->CreateFontWrapper(_device, L"OCR A", &_fontWrapper); //Viner Hand ITC OCR A

	GAPIContextLocator::Provide(new Context_DX{ _device, _context });

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	res = _device->CreateSamplerState(&samplerDesc, &_sampleState);

	_swapchain->SetFullscreenState(true, nullptr);
	RECT desktop;
	const HWND deskWin = GetDesktopWindow();
	GetWindowRect(deskWin, &desktop);
	Resize(desktop.right, desktop.bottom);
}

/******************************************************************************************************************/

void Renderer_DX::Resize(int width, int height)
{
	if (_swapchain) {
		_context->OMSetRenderTargets(0, nullptr, nullptr);

		// Release all outstanding references to the swap chain's buffers.
		_backbuffer->Release();

		HRESULT hr;
		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = _swapchain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

		// Perform error handling here!

		// get the address of the back buffer
		ID3D11Texture2D* p_backbuffer;
		_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_backbuffer));

		// use the back buffer address to create the render target
		_device->CreateRenderTargetView(p_backbuffer, nullptr, &_backbuffer);
		p_backbuffer->Release();
		
		
		_depthStencil->Release();
		D3D11_TEXTURE2D_DESC depth_attachment_desc;
		ZeroMemory(&depth_attachment_desc, sizeof(depth_attachment_desc));
		depth_attachment_desc.Width = Window::TheWindow->_width;
		depth_attachment_desc.Height = Window::TheWindow->_height;
		depth_attachment_desc.MipLevels = 1;
		depth_attachment_desc.ArraySize = 1;
		depth_attachment_desc.Format = DXGI_FORMAT_D32_FLOAT;
		depth_attachment_desc.SampleDesc.Count = 4;
		depth_attachment_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		HRESULT res{ 0 };
		ID3D11Texture2D* p_depth;
		res = _device->CreateTexture2D(&depth_attachment_desc, nullptr, &p_depth);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

		res = _device->CreateDepthStencilView(p_depth, &dsvd, &_depthStencil);
		p_depth->Release();

		// set the render target as the back buffer
		_context->OMSetRenderTargets(1, &_backbuffer, _depthStencil);

		// Set up the viewport.
		D3D11_VIEWPORT vp;
		vp.Width = width;
		vp.Height = height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		_context->RSSetViewports(1, &vp);
	}
}

void Renderer_DX::SwapBuffers()
{
	_swapchain->Present(0, 0);
}

/******************************************************************************************************************/

// Load and prepare shaders
void Renderer_DX::InitialiseShaders()
{
	// load and compile the two shaders
	ID3D10Blob *VS, *PS, *err;
	D3DX11CompileFromFile(L"shaders.hlsl", nullptr, nullptr, "VShader", "vs_4_0", 0, 0, nullptr, &VS, &err, nullptr);

	if (err) {
		char* compileErrors;
		unsigned long bufferSize, i;
		std::ofstream fout;
		// Get a pointer to the error message text buffer.
		compileErrors = static_cast<char*>(err->GetBufferPointer());

		// Get the length of the message.
		bufferSize = err->GetBufferSize();

		// Open a file to write the error message to.
		fout.open("shader-error.txt");

		// Write out the error message.
		for (i = 0; i<bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		// Close the file.
		fout.close();

		// Release the error message.
		err->Release();
		err = nullptr;
	}

	D3DX11CompileFromFile(L"shaders.hlsl", nullptr, nullptr, "PShader", "ps_4_0", 0, 0, nullptr, &PS, &err, nullptr);

	if (err) {
		char* compileErrors;
		unsigned long bufferSize, i;
		std::ofstream fout;
		// Get a pointer to the error message text buffer.
		compileErrors = static_cast<char*>(err->GetBufferPointer());

		// Get the length of the message.
		bufferSize = err->GetBufferSize();

		// Open a file to write the error message to.
		fout.open("shader-error.txt");

		// Write out the error message.
		for (i = 0; i<bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		// Close the file.
		fout.close();

		// Release the error message.
		err->Release();
		err = nullptr;
	}

	// encapsulate both shaders into shader objects
	_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &_vertexShader);
	_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &_pixelShader);

	// set the shader objects
	_context->VSSetShader(_vertexShader, nullptr, 0);
	_context->PSSetShader(_pixelShader, nullptr, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, tangent), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, texcoord), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, colour), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	_device->CreateInputLayout(ied, 5, VS->GetBufferPointer(), VS->GetBufferSize(), &_layout);
	_context->IASetInputLayout(_layout);


	// Create uniform buffer
	UniformBuffer uniforms;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(uniforms);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &uniforms;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the buffer.
	_device->CreateBuffer(&cbDesc, &InitData, &_uniformBuffer);
}

void Renderer_DX::SetFullscreen() const
{
	_swapchain->SetFullscreenState(true, nullptr);
}


/******************************************************************************************************************/

#endif
