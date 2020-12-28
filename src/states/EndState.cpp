#include "EndState.h"
#include "SelectState.h"
#include "../Game.h"
using namespace yothello;

const std::string EndState::REGAME_BUTTON_NAME = "regame_button";
const sf::Vector2f EndState::REGAME_BUTTON_POS{ 700.0f,700.0f };
const sf::IntRect EndState::REGAME_BUTTON_SIZE{ 0,0,100,100 };
const uint32_t EndState::REGAME_BUTTON_ANIMATION_FRAME = 11;

const std::string EndState::EXIT_BUTTON_NAME = "exit_button";
const sf::Vector2f EndState::EXIT_BUTTON_POS{ 700.0f,800.0f };
const sf::IntRect EndState::EXIT_BUTTON_SIZE{ 0,0,100,100 };
const uint32_t EndState::EXIT_BUTTON_ANIMATION_FRAME = 11;


EndState::EndState(Game* game) :
	GameState(game),
	regameButton(REGAME_BUTTON_NAME, REGAME_BUTTON_POS, REGAME_BUTTON_SIZE, REGAME_BUTTON_ANIMATION_FRAME),
	exitButton(EXIT_BUTTON_NAME, EXIT_BUTTON_POS, EXIT_BUTTON_SIZE, EXIT_BUTTON_ANIMATION_FRAME)
{
}

void EndState::enter(Game& game)
{
	game.getBoard().clearPlacables();
	game.getBoard().blackout();
	regameButton.resetColor();

	const int black_score = game.getFooter().getScore(PlayerType::BLACK);
	const int white_score = game.getFooter().getScore(PlayerType::WHITE);
	PlayerType winner;

	if (black_score > white_score) winner = PlayerType::BLACK;
	else if (black_score < white_score) winner = PlayerType::WHITE;
	else winner = PlayerType::NONE;

	game.getAnimationManager().stop();

	GameAnimation& fanfare_animation = game.getPlayerManager().fanfare(winner);
	game.getAnimationManager().push(fanfare_animation);
	game.getAnimationManager().add(regameButton);
	// game.getAnimationManager().add(exitButton);
}

void EndState::exit(Game& game)
{
	game.getAnimationManager().stop();
	game.getBoard().reset();
	auto& settings = game.getFooter().getSettingsButton().getPopup();
	settings.clearVoice();
}

void EndState::nupdate(const MouseInput& mouseInput)
{
	 if (regameButton.onClick(mouseInput))
		owner->changeState(new SelectState(owner));
	//if (exitButton.onClick(mouseInput))
	//	;
}

