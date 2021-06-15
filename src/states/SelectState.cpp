#include "SelectState.h"
#include "PlayState.h"
#include "../Game.h"
using namespace reversi;

const std::string SelectState::SELECT_BLACK_BUTTON_NAME = "select_black";
const std::string SelectState::SELECT_WHITE_BUTTON_NAME = "select_white";
const sf::Vector2f SelectState::SELECT_BLACK_BUTTON_POS{ 0.0f,0.0f };
const sf::Vector2f SelectState::SELECT_WHITE_BUTTON_POS{ 400.0f,0.0f };

SelectState::SelectState(Game* game) :
	GameState(game),
	select_black(SELECT_BLACK_BUTTON_NAME, SELECT_BLACK_BUTTON_POS),
	select_white(SELECT_WHITE_BUTTON_NAME, SELECT_WHITE_BUTTON_POS)
{
	addChild(&select_black);
	addChild(&select_white);
}

void SelectState::enter(Game& game)
{
	game.getBoard().init();
}

void SelectState::exit(Game& game)
{
	auto& playerManager = game.getPlayerManager();
	auto& settings = game.getFooter().getSettingsButton().getPopup();
	settings.registerVoice(*playerManager.getPlayer()->getVoice());
	settings.registerVoice(*playerManager.getAI()->getVoice());

	auto& turnAnimation = game.getPlayerManager().getTurnPlayer()->myTurn();
	game.getAnimationManager().push(turnAnimation);

	Logger::instance().begins();
}

void SelectState::nupdate(const MouseInput& mouseInput)
{
	select_black.setDark();
	select_white.setDark();

	if (select_black.includes(mouseInput.position))
	{
		if (mouseInput.onClick())
		{
			owner->getPlayerManager()
				.setPlayer(PlayerType::BLACK)
				.setAI(PlayerType::WHITE)
				.startTurn();
			owner->getBoard().lightup();
			owner->changeState(new PlayState(owner));
		}
		else
			select_black.resetColor();
	}
	else if (select_white.includes(mouseInput.position))
	{
		if (mouseInput.onClick())
		{
			owner->getPlayerManager()
				.setPlayer(PlayerType::WHITE)
				.setAI(PlayerType::BLACK)
				.startTurn();
			owner->getBoard().lightup();
			owner->changeState(new PlayState(owner));
		}
		else
			select_white.resetColor();
	}
}
