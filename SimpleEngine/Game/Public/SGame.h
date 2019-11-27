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
		virtual void Initialize();
		virtual void Run();
		virtual void ShutDown();

		virtual void Update();
		virtual void Draw();

	private:

		SGameTime* GameTime;

		std::function<void*()> GetWindowHandle;
		std::function<void(SIZE&)> GetRenderTargetSize;




	};
}