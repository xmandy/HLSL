#include "Public/SGameTime.h"

using namespace std::chrono;

namespace SGame
{

	SGameTime::SGameTime()
	{

	}
	SGameTime::~SGameTime()
	{

	}
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

	void SGameTime::SetTotalGameTime(const milliseconds&& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const milliseconds& SGameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void SGameTime::SetElapsedGameTime(const milliseconds& elapseGameTime)
	{
		mElapsedGameTime = elapseGameTime;
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