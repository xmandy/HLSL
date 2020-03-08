#pragma once

#include <DirectXMath.h>
#include <chrono>

#include "Public/SDrawableGameComponent.h"

namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
}

namespace SEngine
{
	class SGameTime;

	class SFpsComponent : public SDrawableGameComponent
	{
		SRTTI_DECLARATIONS(SFpsComponent, SDrawableGameComponent)
	public:
		SFpsComponent(SGame& game);

		SFpsComponent& operator=(const SFpsComponent&) = delete;
		SFpsComponent& operator=(SFpsComponent&&) = default;
		~SFpsComponent() = default;

		DirectX::XMFLOAT2& TextPosition();
		int FrameRate() const;
		
		virtual void Initialize() override;
		virtual void Update(const SGameTime& gameTime);
		virtual void Draw(const SGameTime& gameTime);


	private:
		std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
		std::unique_ptr<DirectX::SpriteFont> mSpriteFont;
		DirectX::XMFLOAT2 mPosition{ 20.f, 20.f };

		int mFrameCount{ 0 };
		int mFrameRate{ 0 };

		std::chrono::microseconds mLastTotalGameTime;

	};
}