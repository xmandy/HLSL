#pragma once
#include "Common/Public/SRHHI.h"

namespace SGame
{
	class SGame;
	class SGameTime;

	class SGameComponent : public Common::SRTTI
	{
		SRTTI_DECLARATIONS(SGameComponent, Common::SRTTI)

	public:
		SGameComponent();
		SGameComponent(SGame& game);

		virtual ~SGameComponent();

		SGame* GetGame() { return mGame; };
		void SetGame(SGame& game) { mGame = &game; };
		bool Enabled() const { return mEnabled; };
		void SetEnabled(bool enabled) { mEnabled = enabled; }


		virtual void Initialize();
		virtual void Update(const SGameTime& gameTime) {};

	protected:
		SGame* mGame;
		bool mEnabled;
	private:
		//SGameComponent(const SGameComponent& rhs);
		//SGameComponent& operator=(const SGameComponent& rhs);
	};

}