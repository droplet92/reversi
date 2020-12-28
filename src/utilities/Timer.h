#pragma once
#include <chrono>
using namespace std::chrono;

namespace yothello
{
	class Timer
	{
	private:
		time_point<steady_clock> prev, cur;
		duration<float> elapsed;
		float lag;

	public:
		Timer() :
			prev(high_resolution_clock::now()),
			elapsed(steady_clock::duration::zero()),
			lag(0.0f)
		{
		}
		~Timer() {}

		float getDelay() const { return lag; }
		float getTick() const { return elapsed.count(); }
		void updateDelay(const float dt) { lag += dt; }

		void record()
		{
			static constexpr float MS_TO_SEC_UNIT = 1000.0f;
			cur = high_resolution_clock::now();
			elapsed = cur - prev;
			prev = cur;
			lag += elapsed.count() * MS_TO_SEC_UNIT;
		}
	};
}