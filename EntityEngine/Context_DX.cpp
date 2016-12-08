#include "Context_DX.h"
#include <iostream>
#include <array>

// Private Methods -----------------------------------------------------------------
bool Context_DX::CreateDeviceAndContext()
{

	unsigned int device_flags{ 0 };

	std::array<D3D_FEATURE_LEVEL, 3> feature_levels = {
		{ D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0 }
	};

	D3D_FEATURE_LEVEL feature_level;

	if (!_device) {
		HRESULT h_result{ 0 };
		h_result = D3D11CreateDevice(nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			device_flags,
			&feature_levels[0],
			feature_levels.size(),
			D3D11_SDK_VERSION,
			&_device,
			&feature_level,
			&_device_context);

		if (FAILED(h_result)) {
			std::cerr << "D3D11CreateDevice Failed." << std::endl;
			return false;
		}

		if (feature_level != D3D_FEATURE_LEVEL_11_0) {
			std::cerr << "Direct3D Feature Level 11 unsupported." << std::endl;
			return false;
		}
	}

	return true;
}

// ---------------------------------------------------------------------------------

bool Context_DX::Create()
{
	return CreateDeviceAndContext();
}

ID3D11Device* Context_DX::GetDevice() const
{
	return _device;
}

ID3D11DeviceContext* Context_DX::GetDeviceContext() const
{
	return _device_context;
}
