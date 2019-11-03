#pragma once

// Standard
#include <iostream>
#include <string>
#include <vector>

// Windows
#include <windows.h>
// do not know its usage
//#include <winrt\Windows.Foundation.h>

// DirectX
#include <d3d11_3.h>
#include <dxgi1_2.h>

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif