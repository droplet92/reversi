#include "PlayerManager.h"
#include "../animations/AnimationEffect.h"
using namespace reversi;

PlayerManager::PlayerManager() :
	player(nullptr),
	ai(nullptr),
	turn(nullptr),
	_draw(GameAnimation::DRAW_NAME, GameAnimation::ANIMATION_POS_BIG, true, fade_in)
{
}

PlayerManager::~PlayerManager()
{
	delete player;
	delete ai;
}

GameAnimation& PlayerManager::fanfare(const PlayerType winner)
{
	if (player->type == winner)
	{
		ai->getVoice()->stop();
		player->getVoice()->fanfare();
		return (player->fanfare_animation);
	}
	else if (ai->type == winner)
	{
		player->getVoice()->stop();
		ai->getVoice()->fanfare();
		return (ai->fanfare_animation);
	}
	else
	{
		player->getVoice()->stop();
		ai->getVoice()->stop();
		return (const_cast<GameAnimation&>(_draw));
	}
}
