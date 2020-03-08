#pragma once

#include <chrono>

namespace SEngine
{
	class SGameTime;

	class SGameClock final
	{
	public:
		SGameClock();
		SGameClock(const SGameClock&) = default;
		SGameClock& operator=(const SGameClock&) = default;
		~SGameClock() = default;

		const std::chrono::high_resolution_clock::time_point& StartTime() const;
		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		const std::chrono::high_resolution_clock::time_point& LastTime() const;

		void Reset();
		void UpdateGameTime(SGameTime& GameTime);

	private:
		std::chrono::high_resolution_clock::time_point SStartTime;
		std::chrono::high_resolution_clock::time_point SCurrentTime;
		std::chrono::high_resolution_clock::time_point SLastTime;


	};
}