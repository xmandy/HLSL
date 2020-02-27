#include "Public/SGame.h"
#include "Public/SGameTime.h"
#include "Public/SGameClock.h"
#include "Common/Public/SException.h"

#include "Components/Public/SGameComponent.h"
#include "Components/Public/SDrawableGameComponent.h"


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

		HRESULT hr = mD3DDevice->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void **>(mDebugInfoQueue.put()));
		if (SUCCEEDED(hr))
		{
			mDebugInfoQueue->ClearRetrievalFilter();
			mDebugInfoQueue->ClearStorageFilter();
			D3D11_INFO_QUEUE_FILTER filter;
			ZeroMemory(&filter, sizeof(filter));
			std::array<D3D11_MESSAGE_SEVERITY, 4> severityList = {
				D3D11_MESSAGE_SEVERITY_CORRUPTION,
				D3D11_MESSAGE_SEVERITY_ERROR,
				D3D11_MESSAGE_SEVERITY_WARNING,
				D3D11_MESSAGE_SEVERITY_INFO,
			};
			filter.AllowList.pSeverityList = severityList.data();
			filter.AllowList.NumSeverities = static_cast<UINT>(severityList.size());

			//mDebugInfoQueue->AddStorageFilterEntries(&filter);
			//mDebugInfoQueue->AddRetrievalFilterEntries(&filter);
			mDebugInfoQueue->PushEmptyStorageFilter();
			/*mDebugInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			mDebugInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
			D3D11_MESSAGE_ID hide[] =
			{
				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS
			};
			D3D11_INFO_QUEUE_FILTER filter{ 0 };
			filter.DenyList.NumIDs = 1;
			filter.DenyList.pIDList = hide;
			mDebugInfoQueue->AddStorageFilterEntries(&filter);
*/
		}

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
		mGameTime = new SGameTime();
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
		SwapChainDesc.SampleDesc.Quality = mMultiSamplingQualityLevel - 1;
		//SwapChainDesc.SampleDesc.Count = 1;
		//SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		// number of back buffers of the swap chain, value of 1 means double buffering,
		// value of 2 means triple buffering.
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// dxgi full-screen desc
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC FullScreenDesc{ 0 };
		FullScreenDesc.RefreshRate.Numerator = mFrameRate;
		FullScreenDesc.RefreshRate.Denominator = 1;
		FullScreenDesc.Windowed = !mFullScreen;

		// DXGI related function
		com_ptr<IDXGIDevice> dxgiDevice;
		//Common::ThrowIfFailed(mD3DDevice->QueryInterface(__uuidof(IDXGIDevice),
		//	reinterpret_cast<void **>(dxgiDevice.put())), "DXGIDevice");
		dxgiDevice = mD3DDevice.as<IDXGIDevice>();

		assert(dxgiDevice != nullptr);
		com_ptr<IDXGIAdapter> dxgiAdapter;
		Common::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.put()), "Adapter");

		com_ptr<IDXGIFactory2> dxgiFactory;
		Common::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.put())),
			"Factory");
		// dxgi related end

		// swap chain is not part of direct3d
		// tasks as presenting rendered frames to the screen and transitioning from windowed to full - screen display modes.
		// These tasks are common across many APIs and are therefore independent of Direct3D.
		void* Window = mGetWindowHandle();
		/*HRESULT hr = dxgiFactory->CreateSwapChainForHwnd(mD3DDevice.get(), reinterpret_cast<HWND>(Window),
			&SwapChainDesc, &FullScreenDesc, nullptr, mSwapChain.put());
		if (FAILED(hr))
		{
			TestDebugMessage();
		}*/
		Common::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(mD3DDevice.get(), reinterpret_cast<HWND>(Window),
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
		DepthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevel - 1;
		Common::ThrowIfFailed(mD3DDevice->CreateTexture2D(&DepthStencilDesc, nullptr, mDepthStencilBuffer.put()),
			"depth stencil");
		CD3D11_DEPTH_STENCIL_VIEW_DESC DSDesc(D3D11_DSV_DIMENSION_TEXTURE2DMS);
		Common::ThrowIfFailed(mD3DDevice->CreateDepthStencilView(mDepthStencilBuffer.get(), &DSDesc, mDepthStencilView.put()));

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
		for (auto comp : mComponents)
		{
			comp->Initialize();
		}
		mGameClock->Reset();
	}
		

	void SGame::Run()
	{
		mGameClock->UpdateGameTime(*mGameTime);
		Update(*mGameTime);
		Draw(*mGameTime);
	}

	void SGame::ShutDown()
	{
		mD3DDeviceContext->ClearState();
		mD3DDeviceContext->Flush();

		mDepthStencilView = nullptr;
		mRenderTargetView = nullptr;
		mSwapChain = nullptr;
		mD3DDeviceContext = nullptr;
		mD3DDevice = nullptr;


	}


	void SGame::Update(const SGameTime& gameTime)
	{
		for (auto comp : mComponents)
		{
			if (comp->Enabled())
			{
				comp->Update(gameTime);
			}
		}

	}

	void SGame::Draw(const SGameTime& gameTime)
	{
		for (auto comp : mComponents)
		{
			SDrawableGameComponent* drawableComp = comp->As<SDrawableGameComponent>();
			if (drawableComp && drawableComp->Visible())
			{
				drawableComp->Draw(gameTime);
			}
			
		}

		static const DirectX::XMVECTORF32 BackgroundColor = { 0.392f, 0.1f, 0.1f, 1.0f };

		mD3DDeviceContext->ClearRenderTargetView(mRenderTargetView.get(), reinterpret_cast<const float*>(&BackgroundColor));
		mD3DDeviceContext->ClearDepthStencilView(mDepthStencilView.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f, 0);

		HRESULT hr = mSwapChain->Present(0, 0);

		Common::ThrowIfFailed(hr, "Swapchain Present() failed");
	}


	void SGame::TestDebugMessage()
	{
		if (!mDebugInfoQueue)
			return;

		UINT64 message_count = mDebugInfoQueue->GetNumStoredMessages();

		for (UINT64 i = 0; i < message_count; i++) 
		{
			SIZE_T message_size = 0;
			mDebugInfoQueue->GetMessage(i, nullptr, &message_size); //get the size of the message

			D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(message_size); //allocate enough space
			HRESULT hr = mDebugInfoQueue->GetMessage(i, message, &message_size); //get the actual message

			//do whatever you want to do with it
			if (SUCCEEDED(hr))
			{
				printf("Directx11: %.*s", message->DescriptionByteLength, message->pDescription);
			}

			free(message);
		}

		mDebugInfoQueue->ClearStoredMessages();
	}
}