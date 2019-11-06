#pragma once
#include "Common/Public/SHeaders.h"
#include "Common/Public/SRHHI.h"

namespace SGame
{
	class SGame : public Common::SRTTI
	{
		SRTTI_DECLARATIONS(SGame, Common::SRTTI)

	public:
		virtual void Initialize();



	};
}