#pragma once
#include "../animations/GameAnimation.h"
#include "../utilities/AnimationQueue.h"
#include <vector>

namespace reversi
{
	class AnimationManager
	{
	private:
		AnimationQueue queue;
		std::vector<GameAnimation*>* playing; // [point_static] guarantees no (done & expires) animations

	public:
		AnimationManager() :
			playing(nullptr)
		{
		}
		~AnimationManager() {}

		bool done() const { return playing->at(0)->done(); }

		void add(GameAnimation& animation);
		void push(GameAnimation& animation);
		void stop() { playing = nullptr; }

		void drawTo(sf::RenderWindow& window);
		bool nupdate(const float dt);
	};
}