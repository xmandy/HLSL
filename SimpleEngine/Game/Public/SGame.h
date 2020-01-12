#pragma once
#include "Common/Public/SHeaders.h"
#include "Common/Public/SRHHI.h"

#include <functional>

namespace SGame
{
	class SGameTime;

	class SGame : public Common::SRTTI
	{
		SRTTI_DECLARATIONS(SGame, Common::SRTTI)

	public:

		SGame(std::function<void*()> GetWindowHandleFunc,
			std::function<void(SIZE&)> GetRenderTargetSizeFunc);
		
		void CreateDeviceResources();
		void CreateWidowSizeDependentResources();

		virtual void Initialize();
		virtual void Run();
		virtual void ShutDown();

		virtual void Update();
		virtual void Draw();

	protected:
		// Device members
		winrt::com_ptr<ID3D11Device> D3DDevice;
		winrt::com_ptr<ID3D11DeviceContext> D3DDeviceContext;
		D3D_FEATURE_LEVEL SelectedFeatureLevel;

		// swap chain
		winrt::com_ptr<IDXGISwapChain1> SwapChain;
		std::uint32_t FrameRate{ 60 };
		bool FullScreen{ false };


		// MSAA members
		std::uint32_t MultiSamplingCount{ 4 };
		std::uint32_t MultiSamplingQualityLevel{ 0 };

	private:

		SGameTime* GameTime;

		std::function<void*()> GetWindowHandle;
		std::function<void(SIZE&)> GetRenderTargetSize;

		SIZE RenderTargetSize;



	};
}