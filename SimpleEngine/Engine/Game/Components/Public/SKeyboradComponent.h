#pragma once
#include <DirectXTK/Inc/Keyboard.h>
#include <memory>

#include "SGameComponent.h"

namespace SEngine{

	class SKeyBoradComponent final : public SGameComponent
	{
		SRTTI_DECLARATIONS(SKeyBoradComponent, SGameComponent)

	public:
		static DirectX::Keyboard* Keyboard();
	};

}