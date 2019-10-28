#pragma once

#include <Windows.h>
#include <string>
#include <functional>
#include <vector>
#include <vector>
#include <iostream>

namespace Platform
{
	class Win32Window final
	{
	public:
		Win32Window();
		~Win32Window();

	private:

	};

	Win32Window::Win32Window()
	{
		std::cout << "HelloWorld" << "\n";
	}

	Win32Window::~Win32Window()
	{
	}

}