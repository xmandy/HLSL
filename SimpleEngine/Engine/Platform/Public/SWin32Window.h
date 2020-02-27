#pragma once

#include "Common/Public/SHeaders.h"

namespace Platform
{
	class Win32Window final
	{
	public:
		Win32Window();
		~Win32Window();

		static void InitializeWindow(WNDCLASSEX &Window, HWND &WindowHandler, HINSTANCE Instance, const std::wstring &ClassName,
			const std::wstring &WindowTitle, const SIZE &RenderTargetSize, int ShowCommand);

		static LRESULT WINAPI WndProc(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
		static POINT CenterWindow(const SIZE& windowSize);

	//private:

	};

}