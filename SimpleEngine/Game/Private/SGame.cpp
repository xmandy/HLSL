#include "Public/SGame.h"
#include "Public/SGameTime.h"
#include "Common/Public/SException.h"

namespace SGame
{

	SGame::SGame(std::function<void*()> GetWindowHandleFunc,
		std::function<void(SIZE&)> GetRenderTargetSizeFunc):
		GetWindowHandle(GetWindowHandleFunc),
		GetRenderTargetSize(GetRenderTargetSizeFunc)
	{

	}

	void SGame::CreateDeviceResources()
	{
		uint32_t CreateFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
		CreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// levels from most to least preferred
		D3D_FEATURE_LEVEL Levels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		ID3D11Device* D3DDevicePtr;
		ID3D11DeviceContext* D3DDeviceContextPtr;

		// create device
		Common::ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			CreateFlags, Levels, ARRAYSIZE(Levels), D3D11_SDK_VERSION, &D3DDevicePtr,
			&SelectedFeatureLevel, &D3DDeviceContextPtr), "Create Device Failed!");

		D3DDeviceContext = std::make_unique<ID3D11DeviceContext>(D3DDeviceContextPtr);
		D3DDevice = std::make_unique<ID3D11Device>(D3DDevicePtr);

		// check multi sample quality levels



	}

	void	 SGame::Initialize()
	{

	}
		

	void SGame::Run()
	{

	}

	void SGame::ShutDown()
	{


	}


	void SGame::Update()
	{

	}

	void SGame::Draw()
	{

	}
}