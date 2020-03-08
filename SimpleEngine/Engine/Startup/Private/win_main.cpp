#include "Common/Public/SHeaders.h"
#include "Common/Public/SException.h"
#include "Platform/Public/SWin32Window.h"
#include "Public/SGame.h"

#pragma comment(lib, "windowsapp")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")



int WINAPI WinMain(HINSTANCE Instance, HINSTANCE, LPSTR, int ShowCommand)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Common::ThrowIfFailed(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED), "ERROR initializing COM.");


	const std::wstring WindowClsName = L"SREngine";
	const std::wstring WindowTitle = L"Main";

	const SIZE RenderTargetSize = { 1024, 768 };
	HWND windowHandle;
	WNDCLASSEX windowCls;

	Platform::Win32Window::InitializeWindow(windowCls, windowHandle, Instance, WindowClsName, WindowTitle, RenderTargetSize, ShowCommand);

	auto getRenderTargetSize = [&RenderTargetSize](SIZE &renderTargetSize)
	{
		renderTargetSize = RenderTargetSize;
	};
	auto getWindow = [&]()->void*
	{
		return reinterpret_cast<void*>(windowHandle);
	};

	SEngine::SGame game(getWindow, getRenderTargetSize);
	game.UpdateRenderTargetSize();
	game.Initialize();

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
			game.Run();
		}
	}

	game.ShutDown();

	UnregisterClass(WindowClsName.c_str(), windowCls.hInstance);

	CoUninitialize();
	return static_cast<int>(Message.wParam);

}


