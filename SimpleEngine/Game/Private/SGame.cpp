#include "Public/SGame.h"
#include "Public/SGameTime.h"
#include "Public/SGameClock.h"
#include "Common/Public/SException.h"


using namespace winrt;

namespace SGame
{

	SRTTI_DEFINITIONS(SGame)

	SGame::SGame(std::function<void*()> GetWindowHandleFunc,
		std::function<void(SIZE&)> GetRenderTargetSizeFunc):
		mGetWindowHandle(GetWindowHandleFunc),
		mGetRenderTargetSize(GetRenderTargetSizeFunc)
	{
		CreateDeviceIndependentResources();
		CreateDeviceResources();
	}



	SGame::~SGame()
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

		winrt::com_ptr<ID3D11Device> D3DDevicePtr;
		winrt::com_ptr<ID3D11DeviceContext> D3DDeviceContextPtr;

		// create device
		Common::ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			CreateFlags, Levels, ARRAYSIZE(Levels), D3D11_SDK_VERSION, D3DDevicePtr.put(),
			&mSelectedFeatureLevel, D3DDeviceContextPtr.put()), "Create Device Failed!");

		mD3DDeviceContext = D3DDeviceContextPtr.as<ID3D11DeviceContext>();
		mD3DDevice = D3DDevicePtr.as<ID3D11Device>();

		// check multi sample quality levels
		Common::ThrowIfFailed(mD3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
			mMultiSamplingCount, &mMultiSamplingQualityLevel), "CheckMultisampleQualityLevels Failed!");
		if (mMultiSamplingQualityLevel == 0)
		{
			throw Common::SException("Unsupported multi-sampling quality");
		}
		




	}

	void SGame::CreateDeviceIndependentResources()
	{
		//mGameTime = new SGameTime();
		mGameClock = new SGameClock();

	}

	void SGame::CreateWindowSizeDependentResources()
	{
		mGetRenderTargetSize(mRenderTargetSize);
		// create swap chain

		// dxgi swap chain desc 
		DXGI_SWAP_CHAIN_DESC1 SwapChainDesc{ 0 };
		SwapChainDesc.Width = mRenderTargetSize.cx;
		SwapChainDesc.Height = mRenderTargetSize.cy;
		SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDesc.SampleDesc.Count = mMultiSamplingCount;
		SwapChainDesc.SampleDesc.Quality = mMultiSamplingQualityLevel;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// number of back buffers of the swap chain, value of 1 means double buffering,
		// value of 2 means triple buffering.
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		// dxgi full-screen desc
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC FullScreenDesc{ 0 };
		FullScreenDesc.RefreshRate.Numerator = mFrameRate;
		FullScreenDesc.RefreshRate.Denominator = 1;
		FullScreenDesc.Windowed = !mFullScreen;

		// DXGI related function
		com_ptr<IDXGIDevice> DXGIDevice;
		Common::ThrowIfFailed(mD3DDevice->QueryInterface(__uuidof(IDXGIDevice),
			reinterpret_cast<void **>(DXGIDevice.put())), "DXGIDevice");

		assert(DXGIDevice != nullptr);
		com_ptr<IDXGIAdapter> Adapter;
		Common::ThrowIfFailed(DXGIDevice->GetAdapter(Adapter.put()), "Adapter");

		com_ptr<IDXGIFactory2> DXGIFactory;
		Common::ThrowIfFailed(DXGIDevice->GetParent(IID_PPV_ARGS(DXGIFactory.put())),
			"Factory");
		// dxgi related end

		// swap chain is not part of direct3d
		// tasks as presenting rendered frames to the screen and transitioning from windowed to full - screen display modes.
		// These tasks are common across many APIs and are therefore independent of Direct3D.
		void* Window = mGetWindowHandle();
		Common::ThrowIfFailed(DXGIFactory->CreateSwapChainForHwnd(DXGIDevice.get(), reinterpret_cast<HWND>(Window),
			&SwapChainDesc, &FullScreenDesc, nullptr, mSwapChain.put()), "SwapChain");

		// render target view
		com_ptr<ID3D11Texture2D> BackBuffer;
		Common::ThrowIfFailed(mSwapChain->GetBuffer(0, IID_PPV_ARGS(BackBuffer.put())), "BackBuffer");
		BackBuffer->GetDesc(&mBackBufferDesc);
		Common::ThrowIfFailed(mD3DDevice->CreateRenderTargetView(BackBuffer.get(), nullptr, mRenderTargetView.put()), "RT");

		// depth-stencil view
		D3D11_TEXTURE2D_DESC DepthStencilDesc{ 0 };
		DepthStencilDesc.Width = mRenderTargetSize.cx;
		DepthStencilDesc.Height = mRenderTargetSize.cy;
		DepthStencilDesc.MipLevels = 1;
		DepthStencilDesc.ArraySize = 1;
		DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		DepthStencilDesc.SampleDesc.Count = mMultiSamplingCount;
		DepthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevel;
		com_ptr<ID3D11Texture2D> DepthStencilBuffer;
		Common::ThrowIfFailed(mD3DDevice->CreateTexture2D(&DepthStencilDesc, nullptr, DepthStencilBuffer.put()),
			"depth stencil");
		CD3D11_DEPTH_STENCIL_VIEW_DESC DSDesc(D3D11_DSV_DIMENSION_TEXTURE2DMS);
		Common::ThrowIfFailed(mD3DDevice->CreateDepthStencilView(DepthStencilBuffer.get(), &DSDesc, mDepthStencilView.put()));

		// bind to pipeline
		ID3D11RenderTargetView* views[] = { mRenderTargetView.get(), };
		mD3DDeviceContext->OMSetRenderTargets(1, views, mDepthStencilView.get());

		// viewport
		mViewport = CD3D11_VIEWPORT(0.0f, 0.0f, static_cast<float>(mRenderTargetSize.cx),
			static_cast<float>(mRenderTargetSize.cy));
		





	}

	void SGame::UpdateRenderTargetSize()
	{
		CreateWindowSizeDependentResources();
	}

	void SGame::Initialize()
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