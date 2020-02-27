#pragma once

#include "Public/SGameComponent.h"

namespace SGame
{
	class SCamera;

	class SDrawableGameComponent: public SGameComponent
	{
		SRTTI_DECLARATIONS(SDrawableGameComponent, SGameComponent)

	public:
		SDrawableGameComponent();
		SDrawableGameComponent(SGame& game);
		SDrawableGameComponent(SGame& game, SCamera& camera);

		virtual ~SDrawableGameComponent();

		bool Visible() const { return mVisible; };
		bool SetVisible(bool visible) { mVisible = visible; }

		SCamera* GetCamera() {return mCamera;}
		void SetCamera(SCamera* cam) { mCamera = cam;}

		virtual void Draw(const SGameTime& gameTime);

	protected:
		bool mVisible;
		SCamera* mCamera;

	private:
		//SDrawableGameComponent(const SDrawableGameComponent& rhs);
		//SDrawableGameComponent& operator=(const SDrawableGameComponent& rhs);

	};
}