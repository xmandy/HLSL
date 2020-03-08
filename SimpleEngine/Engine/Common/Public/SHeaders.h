#pragma once

// Standard
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Windows
#include <windows.h>
// com related headers
#include <winrt/Windows.Foundation.h>

// DirectX
#include <d3d11_3.h>
#include <dxgi1_2.h>

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif