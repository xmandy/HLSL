#include "Public/SKeyboradComponent.h"

using namespace std;
using namespace DirectX;

namespace SEngine
{
	SRTTI_DEFINITIONS(SKeyboardComponent)

		unique_ptr<Keyboard> SKeyboardComponent::sKeyboard(new DirectX::Keyboard);

	Keyboard* SKeyboardComponent::Keyboard()
	{
		return sKeyboard.get();
	}

	SKeyboardComponent::SKeyboardComponent(SGame& game) :
		SGameComponent(game)
	{
	}

	const Keyboard::State& SKeyboardComponent::CurrentState() const
	{
		return mCurrentState;
	}

	const Keyboard::State& SKeyboardComponent::LastState() const
	{
		return mLastState;
	}

	void SKeyboardComponent::Initialize()
	{
		mCurrentState = sKeyboard->GetState();
		mLastState = mCurrentState;
	}

	void SKeyboardComponent::Update(const SGameTime&)
	{
		mLastState = mCurrentState;
		mCurrentState = sKeyboard->GetState();
	}

	bool SKeyboardComponent::IsKeyUp(Keys key) const
	{
		return mCurrentState.IsKeyUp(static_cast<Keyboard::Keys>(key));
	}

	bool SKeyboardComponent::IsKeyDown(Keys key) const
	{
		return mCurrentState.IsKeyDown(static_cast<Keyboard::Keys>(key));
	}

	bool SKeyboardComponent::WasKeyUp(Keys key) const
	{
		return mLastState.IsKeyUp(static_cast<Keyboard::Keys>(key));
	}

	bool SKeyboardComponent::WasKeyDown(Keys key) const
	{
		return mLastState.IsKeyDown(static_cast<Keyboard::Keys>(key));
	}

	bool SKeyboardComponent::WasKeyPressedThisFrame(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyUp(key));
	}

	bool SKeyboardComponent::WasKeyReleasedThisFrame(Keys key) const
	{
		return (IsKeyUp(key) && WasKeyDown(key));
	}

	bool SKeyboardComponent::IsKeyHeldDown(Keys key) const
	{
		return (IsKeyDown(key) && WasKeyDown(key));
	}

}