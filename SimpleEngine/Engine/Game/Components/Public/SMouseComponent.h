#pragma once

#include <windows.h>

#include "Public/SGameComponent.h"
#include "DirectXTK/Inc/Mouse.h"

namespace SEngine
{
	enum class MouseButtons
	{
		Left = 0,
		Right,
		Middle,
		X1,
		X2
	};

	enum class MouseModes
	{
		Absolute = 0,
		Relative
	};

	class SMouseComponent final : public SGameComponent
	{
		SRTTI_DECLARATIONS(SMouseComponent, SGameComponent)

	public:
		static DirectX::Mouse* Mouse();

		explicit SMouseComponent(SGame& game, MouseModes mode = MouseModes::Relative);
		SMouseComponent(const SMouseComponent&) = delete;
		SMouseComponent(SMouseComponent&&) = default;
		SMouseComponent& operator=(const SMouseComponent&) = delete;
		SMouseComponent& operator=(SMouseComponent&&) = default;
		~SMouseComponent() = default;

		const DirectX::Mouse::State& CurrentState() const;
		const DirectX::Mouse::State& LastState() const;

		virtual void Initialize() override;
		virtual void Update(const SGameTime& gameTime) override;
		void SetWindow(HWND window);

		int X() const;
		int Y() const;
		int Wheel() const;

		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;
		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;
		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;
		bool IsButtonHeldDown(MouseButtons Button) const;

		MouseModes Mode() const;
		void SetMode(MouseModes mode);

	private:
		bool GetButtonState(const DirectX::Mouse::State& state, MouseButtons button) const;

		static std::unique_ptr<DirectX::Mouse> sMouse;

		DirectX::Mouse::State mCurrentState;
		DirectX::Mouse::State mLastState;
	};

}