#include "Public/SGame.h"
#include "Public/SGameTime.h"
#include "Common/Public/SException.h"


using namespace winrt;

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

		winrt::com_ptr<ID3D11Device> D3DDevicePtr;
		winrt::com_ptr<ID3D11DeviceContext> D3DDeviceContextPtr;

		// create device
		Common::ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			CreateFlags, Levels, ARRAYSIZE(Levels), D3D11_SDK_VERSION, D3DDevicePtr.put(),
			&SelectedFeatureLevel, D3DDeviceContextPtr.put()), "Create Device Failed!");

		D3DDeviceContext = D3DDeviceContextPtr.as<ID3D11DeviceContext>();
		D3DDevice = D3DDevicePtr.as<ID3D11Device>();

		// check multi sample quality levels
		Common::ThrowIfFailed(D3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
			MultiSamplingCount, &MultiSamplingQualityLevel), "CheckMultisampleQualityLevels Failed!");
		if (MultiSamplingQualityLevel == 0)
		{
			throw Common::SException("Unsupported multi-sampling quality");
		}
		




	}

	void SGame::CreateWidowSizeDependentResources()
	{
		GetRenderTargetSize(RenderTargetSize);
		// create swap chain

		// dxgi swap chain desc 
		DXGI_SWAP_CHAIN_DESC1 SwapChainDesc{ 0 };
		SwapChainDesc.Width = RenderTargetSize.cx;
		SwapChainDesc.Height = RenderTargetSize.cy;
		SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDesc.SampleDesc.Count = MultiSamplingCount;
		SwapChainDesc.SampleDesc.Quality = MultiSamplingQualityLevel;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// number of back buffers of the swap chain, value of 1 means double buffering,
		// value of 2 means triple buffering.
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		// dxgi full-screen desc
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC FullScreenDesc{ 0 };
		FullScreenDesc.RefreshRate.Numerator = FrameRate;
		FullScreenDesc.RefreshRate.Denominator = 1;
		FullScreenDesc.Windowed = !FullScreen;

		// DXGI related function
		com_ptr<IDXGIDevice> DXGIDevice;
		Common::ThrowIfFailed(D3DDevice->QueryInterface(__uuidof(IDXGIDevice),
			reinterpret_cast<void **>(DXGIDevice.put())), "DXGIDevice");
		assert(DXGIDevice != nullptr);
		com_ptr<IDXGIAdapter> Adapter;
		Common::ThrowIfFailed(DXGIDevice->GetAdapter(Adapter.put()), "Adapter");
		com_ptr<IDXGIFactory2> DXGIFactory;
		Common::ThrowIfFailed(DXGIDevice->GetParent(IID_PPV_ARGS(DXGIFactory.put())),
			"Factory");

		void* Window = GetWindowHandle();
		Common::ThrowIfFailed(DXGIFactory->CreateSwapChainForHwnd(DXGIDevice.get(), reinterpret_cast<HWND>(Window),
			&SwapChainDesc, &FullScreenDesc, nullptr, SwapChain.put()), "SwapChain");

		// render target view
		com_ptr<ID3D11Texture2D> BackBuffer;
		Common::ThrowIfFailed(SwapChain->GetBuffer(0, IID_PPV_ARGS(BackBuffer.put())), "BackBuffer");
		BackBuffer->GetDesc(&BackBufferDesc);
		Common::ThrowIfFailed(D3DDevice->CreateRenderTargetView(BackBuffer.get(), nullptr, RenderTargetView.put()), "RT");

		// depth-stencil view
		D3D11_TEXTURE2D_DESC DepthStencilDesc{ 0 };
		DepthStencilDesc.Width = RenderTargetSize.cx;
		DepthStencilDesc.Height = RenderTargetSize.cy;
		DepthStencilDesc.MipLevels = 1;
		DepthStencilDesc.ArraySize = 1;
		DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		DepthStencilDesc.SampleDesc.Count = MultiSamplingCount;
		DepthStencilDesc.SampleDesc.Quality = MultiSamplingQualityLevel;
		com_ptr<ID3D11Texture2D> DepthStencilBuffer;
		Common::ThrowIfFailed(D3DDevice->CreateTexture2D(&DepthStencilDesc, nullptr, DepthStencilBuffer.put()),
			"depth stencil");
		CD3D11_DEPTH_STENCIL_VIEW_DESC DSDesc(D3D11_DSV_DIMENSION_TEXTURE2DMS);
		Common::ThrowIfFailed(D3DDevice->CreateDepthStencilView(DepthStencilBuffer.get(), &DSDesc, DepthStencilView.put()));

		// bind to pipeline
		D3DDeviceContext->OMSetRenderTargets(1, &(RenderTargetView.get()), DepthStencilView.get());

		// viewport





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