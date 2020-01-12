#pragma once
#include "Common/Public/SHeaders.h"
#include "Common/Public/SRHHI.h"

#include <functional>

namespace SGame
{
	// here use ptr, in order to not include the head file.
	class SGameTime;
	class SGameClock;

	class SGame : public Common::SRTTI
	{
		SRTTI_DECLARATIONS(SGame, Common::SRTTI)

	public:

		SGame(std::function<void*()> GetWindowHandleFunc,
			std::function<void(SIZE&)> GetRenderTargetSizeFunc);

		~SGame();
		
		void CreateDeviceResources();

		void CreateWindowSizeDependentResources();

		void CreateDeviceIndependentResources();


		void UpdateRenderTargetSize();

		virtual void Initialize();
		virtual void Run();
		virtual void ShutDown();

		virtual void Update();
		virtual void Draw();

	protected:
		// Device members
		winrt::com_ptr<ID3D11Device> mD3DDevice;
		winrt::com_ptr<ID3D11DeviceContext> mD3DDeviceContext;
		D3D_FEATURE_LEVEL mSelectedFeatureLevel;

		// MSAA members
		std::uint32_t mMultiSamplingCount{ 4 };
		std::uint32_t mMultiSamplingQualityLevel{ 0 };

		// swap chain
		winrt::com_ptr<IDXGISwapChain1> mSwapChain;
		std::uint32_t mFrameRate{ 60 };
		bool mFullScreen{ false };
		D3D11_TEXTURE2D_DESC mBackBufferDesc;
		winrt::com_ptr<ID3D11RenderTargetView> mRenderTargetView;
		winrt::com_ptr<ID3D11DepthStencilView> mDepthStencilView;

		// view port
		D3D11_VIEWPORT mViewport;



	private:

		SGameClock* mGameClock;
		SGameTime* mGameTime;

		std::function<void*()> mGetWindowHandle;
		std::function<void(SIZE&)> mGetRenderTargetSize;

		SIZE mRenderTargetSize;



	};
}