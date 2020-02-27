#include "Public/SGameClock.h"
#include "Public/SGameTime.h"

using namespace std::chrono;

namespace SGame {

	SGameClock::SGameClock()
	{
		Reset();
	}

	const std::chrono::high_resolution_clock::time_point& SGameClock::StartTime() const
	{
		return SStartTime;

	}

	const std::chrono::high_resolution_clock::time_point& SGameClock::CurrentTime() const
	{
		return SCurrentTime;

	}

	const std::chrono::high_resolution_clock::time_point& SGameClock::LastTime() const
	{
		return SLastTime;
	}

	void SGameClock::Reset()
	{
		SStartTime = high_resolution_clock::now();
		SCurrentTime = SStartTime;
		SLastTime = SCurrentTime;
	}

	void SGameClock::UpdateGameTime(SGameTime& GameTime)
	{
		SCurrentTime = high_resolution_clock::now();

		GameTime.SetCurrentTime(SCurrentTime);
		GameTime.SetTotalGameTime(duration_cast<milliseconds>(SCurrentTime - SStartTime));
		GameTime.SetElapsedGameTime(duration_cast<milliseconds>(SCurrentTime - SLastTime));

		SLastTime = SCurrentTime;

	}


}