#include "TitleState.h"
#include "SelectState.h"
#include "../Game.h"
#include "../animations/AnimationEffect.h"
using namespace yothello;

TitleState::TitleState(Game* game) :
	GameState(game),
	_game_title(GameAnimation::TITLE_NAME, GameAnimation::ANIMATION_POS_SMALL, GameAnimation::EXPIRES, fade_in)
{
}

void TitleState::enter(Game& game)
{
	game.getAnimationManager().push(_game_title);
}

void TitleState::exit(Game& game)
{
	game.getAnimationManager().stop();
}

void TitleState::nupdate(const MouseInput& mouseInput)
{
	if (mouseInput.onClick())
		owner->changeState(new SelectState(owner));
}
