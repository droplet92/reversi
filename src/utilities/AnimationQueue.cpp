#include "AnimationQueue.h"
using namespace reversi;

void AnimationQueue::enqueue(GameAnimation& animation)
{
	if (animation.done()) return;
	queue.push(new std::vector{ &animation });
}

std::vector<GameAnimation*>* AnimationQueue::dequeue()
{
	if (queue.empty()) return nullptr;
	auto animationVector = queue.front();
	queue.pop();
	return animationVector;
}
