#include "Common/Public/SHeaders.h"
#include "Platform/Public/SWin32Window.h"
#include "Game/Public/SGame.h"


int WINAPI WinMain(HINSTANCE Instance, HINSTANCE, LPSTR, int ShowCommand)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	const std::wstring WindowClsName = L"SREngine";
	const std::wstring WindowTitle = L"Main";

	const SIZE RenderTargetSize = { 1024, 768 };
	HWND WindowHandle;
	WNDCLASSEX WindowCls;

	Platform::Win32Window::InitializeWindow(WindowCls, WindowHandle, Instance, WindowClsName, WindowTitle, RenderTargetSize, ShowCommand);

	MSG Message{ 0 };

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}

	UnregisterClass(WindowClsName.c_str(), WindowCls.hInstance);

}


