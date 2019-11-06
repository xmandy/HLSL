#include "Public/SGameTime.h"

using namespace std::chrono;

namespace SGame
{
	const high_resolution_clock::time_point& SGameTime::CurrentTime() const
	{
		return mCurrentTime;
	}

	void SGameTime::SetCurrentTime(const high_resolution_clock::time_point& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const milliseconds& SGameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void SGameTime::SetTotalGameTime(const milliseconds& totalSGameTime)
	{
		mTotalGameTime = totalSGameTime;
	}

	const milliseconds& SGameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void SGameTime::SetElapsedGameTime(const milliseconds& elapsedSGameTime)
	{
		mElapsedGameTime = elapsedSGameTime;
	}

	duration<float> SGameTime::TotalGameTimeSeconds() const
	{
		return duration_cast<duration<float>>(mTotalGameTime);
	}

	duration<float> SGameTime::ElapsedGameTimeSeconds() const
	{
		return duration_cast<duration<float>>(mElapsedGameTime);
	}
}