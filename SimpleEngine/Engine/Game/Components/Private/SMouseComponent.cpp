#include "Public/SMouseComponent.h"
#include "Public/SGame.h"

using namespace std;
using namespace DirectX;

namespace SEngine
{
	SRTTI_DEFINITIONS(SMouseComponent)

		unique_ptr<Mouse> SMouseComponent::sMouse(new DirectX::Mouse);

	Mouse* SMouseComponent::Mouse()
	{
		return sMouse.get();
	}

	SMouseComponent::SMouseComponent(SGame& game, MouseModes mode) :
		SGameComponent(game)
	{
		auto getWindow = mGame->GetWindowFunc();
		sMouse->SetWindow(reinterpret_cast<HWND>(getWindow()));
		sMouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	const Mouse::State& SMouseComponent::CurrentState() const
	{
		return mCurrentState;
	}

	const Mouse::State& SMouseComponent::LastState() const
	{
		return mLastState;
	}

	void SMouseComponent::Initialize()
	{
		mCurrentState = sMouse->GetState();
		mLastState = mCurrentState;
	}

	void SMouseComponent::Update(const SGameTime&)
	{
		mLastState = mCurrentState;
		mCurrentState = sMouse->GetState();
	}

	void SMouseComponent::SetWindow(HWND window)
	{
		sMouse->SetWindow(window);
	}

	int SMouseComponent::X() const
	{
		return mCurrentState.x;
	}

	int SMouseComponent::Y() const
	{
		return mCurrentState.y;
	}

	int SMouseComponent::Wheel() const
	{
		return mCurrentState.scrollWheelValue;
	}

	bool SMouseComponent::IsButtonUp(MouseButtons button) const
	{
		return GetButtonState(mCurrentState, button) == false;
	}

	bool SMouseComponent::IsButtonDown(MouseButtons button) const
	{
		return GetButtonState(mCurrentState, button);
	}

	bool SMouseComponent::WasButtonUp(MouseButtons button) const
	{
		return GetButtonState(mLastState, button) == false;
	}

	bool SMouseComponent::WasButtonDown(MouseButtons button) const
	{
		return GetButtonState(mLastState, button);
	}

	bool SMouseComponent::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonUp(button));
	}

	bool SMouseComponent::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return (IsButtonUp(button) && WasButtonDown(button));
	}

	bool SMouseComponent::IsButtonHeldDown(MouseButtons button) const
	{
		return (IsButtonDown(button) && WasButtonDown(button));
	}

	MouseModes SMouseComponent::Mode() const
	{
		auto state = sMouse->GetState();
		return static_cast<MouseModes>(state.positionMode);
	}

	void SMouseComponent::SetMode(MouseModes mode)
	{
		sMouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	bool SMouseComponent::GetButtonState(const Mouse::State& state, MouseButtons button) const
	{
		switch (button)
		{
		case MouseButtons::Left:
			return state.leftButton;

		case MouseButtons::Right:
			return state.rightButton;

		case MouseButtons::Middle:
			return state.middleButton;

		case MouseButtons::X1:
			return state.xButton1;

		case MouseButtons::X2:
			return state.xButton2;

		default:
			throw exception("Invalid MouseButtons.");
		}
	}

}