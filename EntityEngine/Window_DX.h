/***************************************************/
// DX code based on http://www.directxtutorial.com //
/***************************************************/

#pragma once
#if BUILD_DIRECTX
#include "Window.h"

// include Windows and Direct3D headers
#include <windows.h>
#include <windowsx.h>
#include <DirectXMath.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class Window_DX : public Window {
private:

	HWND _hWnd;

public:
	Window_DX(Game* game, int width, int height);

	virtual ~Window_DX();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Initialise() override;
};

#endif
