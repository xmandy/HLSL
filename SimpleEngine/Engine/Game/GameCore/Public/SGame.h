#pragma once
#include "Common/Public/SHeaders.h"
#include "Common/Public/SRHHI.h"
#include "Public/SServiceManager.h"

#include <functional>

namespace SEngine
{
	// here use ptr, in order to not include the head file.
	class SGameTime;
	class SGameClock;
	class SGameComponent;

	class SKeyboardComponent;
	class SMouseComponent;

	class SGame : public Common::SRTTI
	{
		SRTTI_DECLARATIONS(SGame, Common::SRTTI)

	public:
		ID3D11DeviceContext3* Direct3DDeviceContext() const 
		{ return mD3DDeviceContext.get();  }
		ID3D11Device3* Direct3DDevice() const {
			return mD3DDevice.get();
		}


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

		virtual void Update(const SGameTime& gameTime);
		virtual void Draw(const SGameTime& gameTime);

		std::function<void* ()> GetWindowFunc() { return mGetWindowHandle; }

		SServiceManager& Services() { return mServices; }



		void TestDebugMessage();
		/**********************************************/
		// Components Functions
		const std::vector<std::shared_ptr<SGameComponent>>& Components() const { return mComponents; }
		/**********************************************/


	/**********************************************/
	// Render/Device Members
	protected:
		// Device members
		winrt::com_ptr<ID3D11Device3>								mD3DDevice;
		winrt::com_ptr<ID3D11DeviceContext3>						mD3DDeviceContext;
		D3D_FEATURE_LEVEL											mSelectedFeatureLevel;

		// debug members
		winrt::com_ptr<ID3D11InfoQueue>								mDebugInfoQueue;

		// MSAA members
		std::uint32_t												mMultiSamplingCount{ 4 };
		std::uint32_t												mMultiSamplingQualityLevel{ 0 };

		// swap chain
		winrt::com_ptr<IDXGISwapChain1>								mSwapChain;
		std::uint32_t												mFrameRate{ 60 };
		bool														mFullScreen{ false };
		D3D11_TEXTURE2D_DESC										mBackBufferDesc;
		winrt::com_ptr<ID3D11RenderTargetView>						mRenderTargetView;

		// depth stencil buffer/ view
		winrt::com_ptr<ID3D11DepthStencilView>						mDepthStencilView;
		winrt::com_ptr<ID3D11Texture2D>								mDepthStencilBuffer;

		// view port
		D3D11_VIEWPORT												mViewport;
	/**********************************************/



	/******************************************************/
	// Engine Common Members
	private:
		SGameClock*													mGameClock{ nullptr };
		SGameTime*													mGameTime{ nullptr };

		std::function<void*()>										mGetWindowHandle;
		std::function<void(SIZE&)>									mGetRenderTargetSize;

		SIZE mRenderTargetSize;
	/******************************************************/

	/******************************************************/
	// Game Components Members
	private:
		std::vector<std::shared_ptr<SGameComponent>>				mComponents;

	/******************************************************/

	
	/******************************************************/
	// Service Components 
	std::shared_ptr<SKeyboardComponent>								mKeyboard;
	std::shared_ptr<SMouseComponent>								mMouse;
	/******************************************************/

	SServiceManager													mServices;


	};
}