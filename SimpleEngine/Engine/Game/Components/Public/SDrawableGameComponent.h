#pragma once

#include "Public/SGameComponent.h"

namespace SEngine
{
	class SCamera;

	class SDrawableGameComponent: public SGameComponent
	{
		SRTTI_DECLARATIONS(SDrawableGameComponent, SGameComponent)

	public:
		SDrawableGameComponent(): SGameComponent() {};
		SDrawableGameComponent(SGame& game): SGameComponent(game) {};
		SDrawableGameComponent(SGame& game, SCamera& camera) :
			SGameComponent(game), mCamera(&camera)
		{
		}

		virtual ~SDrawableGameComponent() { mCamera = nullptr; };

		bool Visible() const { return mVisible; };
		bool SetVisible(bool visible) { mVisible = visible; }

		SCamera* GetCamera() {return mCamera;}
		void SetCamera(SCamera* cam) { mCamera = cam;}

		virtual void Draw(const SGameTime& gameTime) {};

	protected:
		bool mVisible{ true };
		SCamera* mCamera{ nullptr };

	private:
		//SDrawableGameComponent(const SDrawableGameComponent& rhs);
		//SDrawableGameComponent& operator=(const SDrawableGameComponent& rhs);

	};
}