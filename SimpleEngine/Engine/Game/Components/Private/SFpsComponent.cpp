#include "Public/SFpsComponent.h"
#include "Public/SGame.h"
#include "Public/SResourceEnv.h"
#include "Public/SString.h"
#include "Public/SGameTime.h"
#include "Public/SHeaders.h"

#include "Public/SMouseComponent.h"


#include "DirectXTK/Inc/SpriteBatch.h"
#include "DirectXTK/Inc/SpriteFont.h"

#include <sstream>

using namespace DirectX;
using namespace std;

namespace SEngine {
	SRTTI_DEFINITIONS(SFpsComponent)


	SFpsComponent::SFpsComponent(SGame& game)
		: SDrawableGameComponent(game),
		mSpriteBatch(nullptr),
		mSpriteFont(nullptr),
		mPosition(0.0f, 60.0f),
		mFrameRate(0),
		mFrameCount(0),
		mLastTotalGameTime(0)
	{
		mEnabled = true;

	}

	DirectX::XMFLOAT2& SFpsComponent::TextPosition()
	{
		return mPosition;
	}

	int SFpsComponent::FrameRate() const
	{
		return mFrameRate;
	}


	void SFpsComponent::Initialize()
	{
		mSpriteBatch = make_unique<SpriteBatch>(mGame->Direct3DDeviceContext());

		mSpriteFont = make_unique<SpriteFont>(mGame->Direct3DDevice(),// L"test");
			string2wstring(GetFontPath("Arial_14_Regular.spritefont")).c_str());

	}

	void SFpsComponent::Update(const SGameTime& gameTime)
	{
		if (gameTime.TotalGameTime() - mLastTotalGameTime >= 1.0s)
		{
			mLastTotalGameTime = gameTime.TotalGameTime();
			mFrameRate = mFrameCount;
			mFrameCount = 0;
		}
		++mFrameCount;
	}

	void SFpsComponent::Draw(const SGameTime& gameTime)
	{
		mSpriteBatch->Begin();
		wostringstream fpsLabel;
		fpsLabel << setprecision(4) << L"Frame Rate: " << mFrameRate << \
			L"    Total Elapsed Time: " << gameTime.TotalGameTimeSeconds().count();
		mSpriteFont->DrawString(mSpriteBatch.get(), fpsLabel.str().c_str(), mPosition);
		XMFLOAT2 pos1(mPosition.x, mPosition.y + 20);
		wostringstream mouseLabel;
		auto mouseComp = reinterpret_cast<SMouseComponent*>(mGame->Services().GetService(SMouseComponent::TypeIdClass()));
		mouseLabel << L"Mouse Position: " << mouseComp->X() << L", " << mouseComp->Y() << " Mouse Wheel: "\
			<< mouseComp->Wheel();
		mSpriteFont->DrawString(mSpriteBatch.get(), mouseLabel.str().c_str(), pos1);



		mSpriteBatch->End();
	}




	
}