#include "Public/SWin32Window.h"

#include <DirectXTK/Inc/Mouse.h>
#include <DirectXTK/Inc/Keyboard.h>

namespace Platform
{

	Win32Window::Win32Window()
	{
		std::cout << "HelloWorld" << "\n";
	}

	Win32Window::~Win32Window()
	{
	}

	void Win32Window::InitializeWindow(WNDCLASSEX &Window, HWND &WindowHandle, HINSTANCE Instance, const std::wstring &ClassName,
		const std::wstring &WindowTitle, const SIZE &RenderTargetSize, int ShowCommand)
	{
		ZeroMemory(&Window, sizeof(Window));
		Window.cbSize = sizeof(WNDCLASSEX);
		Window.style = CS_CLASSDC;
		Window.lpfnWndProc = WndProc;
		Window.hInstance = Instance;
		Window.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		Window.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		Window.hCursor = LoadCursor(nullptr, IDC_ARROW);
		Window.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
		Window.lpszClassName = ClassName.c_str();

		RECT WindowRectangle = { 0, 0, RenderTargetSize.cx, RenderTargetSize.cy };
		AdjustWindowRect(&WindowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

		RegisterClassEx(&Window);
		POINT Center = CenterWindow(RenderTargetSize);
		WindowHandle = CreateWindow(ClassName.c_str(), WindowTitle.c_str(), WS_OVERLAPPEDWINDOW, Center.x, Center.y,
			WindowRectangle.right - WindowRectangle.left, WindowRectangle.bottom - WindowRectangle.top, nullptr, nullptr, Instance, nullptr);

		ShowWindow(WindowHandle, ShowCommand);
		UpdateWindow(WindowHandle);
	}

	POINT Win32Window::CenterWindow(const SIZE& WindowSize)
	{
		int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		POINT Center;
		Center.x = (ScreenWidth - WindowSize.cx) / 2;
		Center.y = (ScreenHeight - WindowSize.cy) / 2;

		return Center;
	}


	LRESULT WINAPI Win32Window::WndProc(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		switch (Message)
		{

		case WM_ACTIVATEAPP:
			DirectX::Keyboard::ProcessMessage(Message, WParam, LParam);
			DirectX::Mouse::ProcessMessage(Message, WParam, LParam);
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			DirectX::Keyboard::ProcessMessage(Message, WParam, LParam);
			break;

		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
			DirectX::Mouse::ProcessMessage(Message, WParam, LParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		}

		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}
}