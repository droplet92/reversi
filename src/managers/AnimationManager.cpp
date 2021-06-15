#include "AnimationManager.h"
using namespace reversi;

void AnimationManager::add(GameAnimation& animation)
{
	animation.init();
	if (animation.done()) return;
	playing->push_back(&animation);
}

void AnimationManager::push(GameAnimation& animation)
{
	animation.init();
	queue.enqueue(animation);
	if (!playing && !queue.empty())
		playing = queue.dequeue();
}

void AnimationManager::drawTo(sf::RenderWindow& window)
{
	if (!playing) return;
	for (auto& animation : *playing)
		animation->drawTo(window);
}

bool AnimationManager::nupdate(const float dt)
{
	if (!playing && !queue.empty())
		playing = queue.dequeue();

	if (playing)
	{
		for (auto& animation : *playing)
			animation->update(dt);

		if (playing->at(0)->expired())
		{
			playing = nullptr;
			return false;
		}
		return (playing->at(0)->done());
	}
	return true;
}
