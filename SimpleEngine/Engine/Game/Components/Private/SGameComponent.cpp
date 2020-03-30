#include "Components/Public/SGameComponent.h"

namespace SEngine
{
	SRTTI_DEFINITIONS(SGameComponent)

	SGameComponent::SGameComponent()
		:mGame(nullptr), mEnabled(true)
	{

	}
	SGameComponent::SGameComponent(SGame& game)
		:mGame(&game), mEnabled(true)
	{

	}

	SGameComponent::~SGameComponent()
	{

	}

	void SGameComponent::Initialize()
	{

	}

}