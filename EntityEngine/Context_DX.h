#ifndef GLACIER_ENGINE_D3D_CONTEXT_H_
#define GLACIER_ENGINE_D3D_CONTEXT_H_

#include <D3D/d3d11.h>
#include "GAPIContext.h"

class Context_DX : public GAPIContext {
private:
	bool CreateDeviceAndContext();

protected:
	ID3D11Device* _device;
	ID3D11DeviceContext* _device_context;

public:
	Context_DX() = default;

	Context_DX(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		: _device(device), _device_context(deviceContext)
	{
	}

	~Context_DX()
	{
		_device->Release();
		_device_context->Release();
	}

	bool Create() override;

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;
};

#endif //GLACIER_ENGINE_D3D_CONTEXT_H_
