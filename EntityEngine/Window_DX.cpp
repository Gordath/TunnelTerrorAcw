#if BUILD_DIRECTX
#include "Window_DX.h"
#include "Renderer_DX.h"
#include "Game.h"


/******************************************************************************************************************/

Window_DX::Window_DX(Game* game, int width, int height)
	: Window(game, width, height)
{
	// Reset RNG
	srand(time(nullptr));

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Window_DX::WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = {0, 0, _width, _height};
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	_hWnd = CreateWindowEx(NULL,
	                           L"WindowClass",
	                           L"Tunnel Terror",
	                           WS_OVERLAPPEDWINDOW,
	                           300,
	                           300,
	                           wr.right - wr.left,
	                           wr.bottom - wr.top,
	                           nullptr,
	                           nullptr,
	                           GetModuleHandle(nullptr),
	                           nullptr);
	ShowCursor(false);
	ShowWindow(_hWnd, SW_SHOWDEFAULT);
}

/******************************************************************************************************************/

Window_DX::~Window_DX()
{
}

/******************************************************************************************************************/

// This is the main message handler for the program
LRESULT CALLBACK Window_DX::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		TheWindow->GetGame()->OnResize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		TheWindow->GetGame()->OnKeyboard(wParam, true);
		break;
	case WM_KEYUP:
		TheWindow->GetGame()->OnKeyboard(wParam, false);
		break;
	case WM_MOUSEMOVE:
		TheWindow->_cursorX = GET_X_LPARAM(lParam);
		TheWindow->_cursorY = GET_Y_LPARAM(lParam);
		TheWindow->GetGame()->OnMouseMove(TheWindow->_cursorX, TheWindow->_cursorY);
		break;
	case WM_LBUTTONDOWN:
		TheWindow->GetGame()->OnMouseClick(MouseButtonType::L_BUTTON, TheWindow->_cursorX, TheWindow->_cursorY, true);
		break;
	case WM_LBUTTONUP:
		TheWindow->GetGame()->OnMouseClick(MouseButtonType::L_BUTTON, TheWindow->_cursorX, TheWindow->_cursorY, false);
		break;
	case WM_LBUTTONDBLCLK:
		break;
	case WM_MBUTTONDOWN:
		TheWindow->GetGame()->OnMouseClick(MouseButtonType::M_BUTTON, TheWindow->_cursorX, TheWindow->_cursorY, true);
		break;
	case WM_MBUTTONUP:
		TheWindow->GetGame()->OnMouseClick(MouseButtonType::M_BUTTON, TheWindow->_cursorX, TheWindow->_cursorY, false);
		break;
	case WM_RBUTTONDOWN:
		TheWindow->GetGame()->OnMouseClick(MouseButtonType::R_BUTTON, TheWindow->_cursorX, TheWindow->_cursorY, true);
		break;
	case WM_RBUTTONUP:
		TheWindow->GetGame()->OnMouseClick(MouseButtonType::R_BUTTON, TheWindow->_cursorX, TheWindow->_cursorY, false);
		break;
	case WM_RBUTTONDBLCLK:
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

/******************************************************************************************************************/

void Window_DX::Initialise()
{
	// Initialise DirectX
	_renderer = new Renderer_DX(_hWnd);
	_renderer->Initialise(_width, _height);

	// Setup Game
	_game->Initialise(this);

	MSG msg;
	while (!_game->GetQuitFlag()) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		_game->Run();
	}

	// Clean up DirectX
	_renderer->Destroy();
}

/******************************************************************************************************************/

#endif
