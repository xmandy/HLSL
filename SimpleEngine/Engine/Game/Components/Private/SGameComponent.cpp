#include "Components/Public/SGameComponent.h"

namespace SEngine
{
	SRTTI_DEFINITIONS(SGameComponent)

	SGameComponent::SGameComponent()
		:mGame(nullptr), mEnabled(false)
	{

	}
	SGameComponent::SGameComponent(SGame& game)
		:mGame(&game), mEnabled(false)
	{

	}

	SGameComponent::~SGameComponent()
	{

	}

	void SGameComponent::Initialize()
	{

	}

}