#pragma once
#include "../animations/GameAnimation.h"
#include <queue>
#include <vector>

namespace reversi
{
	// AnimationQueue guarantees queue has no done animations
	class AnimationQueue
	{
	private:
		std::queue<std::vector<GameAnimation*>*> queue;	// [point_static]

	public:
		AnimationQueue() {}
		~AnimationQueue() {}

		bool empty() const { return queue.empty(); }

		void enqueue(GameAnimation& animation);
		[[nodiscard]] std::vector<GameAnimation*>* dequeue();
	};
}