#pragma once
#include "Common/Public/SHeaders.h"
#include "Common/Public/SRHHI.h"

namespace SGame
{
	class SGameTime;

	class SGame : public Common::SRTTI
	{
		SRTTI_DECLARATIONS(SGame, Common::SRTTI)

	public:
		virtual void Initialize();
		virtual void Run();
		virtual void ShutDown();

		virtual void Update();
		virtual void Draw();

	private:

		SGameTime* GameTime;



	};
}