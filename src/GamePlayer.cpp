#include "GamePlayer.h"
#include "animations/AnimationEffect.h"

using namespace reversi;

const std::string GamePlayer::FANFARE_SUFFIX = "_win";


GamePlayer::GamePlayer(const PlayerType type, GameAnimation* _loading) :
	fanfare_animation(
	((type == PlayerType::BLACK) ? GameAnimation::BLACK_NAME : GameAnimation::WHITE_NAME) + FANFARE_SUFFIX,
		GameAnimation::ANIMATION_POS_BIG,
		GameAnimation::EXPIRES,
		fade_in
	),
	type(type),
	voice(new Jukebox((type == PlayerType::BLACK) ? Jukebox::SOUND_BLACK : Jukebox::SOUND_WHITE)),
	loading(_loading)
{
}

GamePlayer::~GamePlayer()
{
	delete loading;
	delete voice;
}
