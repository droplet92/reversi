#include "GameBoardFooter.h"
using namespace reversi;

const std::string GameBoardFooter::FOOTER_NAME = "footer";
const sf::Vector2f GameBoardFooter::FOOTER_POS{ 0.f,800.f };
const sf::IntRect GameBoardFooter::FOOTER_SIZE{ 0,0,800,100 };

const std::string GameBoardFooter::SETTINGS_BUTTON_NAME = "settings_button";
const sf::Vector2f GameBoardFooter::SETTINGS_BUTTON_POS{ 725.f,825.f };
const sf::IntRect GameBoardFooter::SETTINGS_BUTTON_SIZE{ 0,0,50,50 };

const sf::Vector2f GameBoardFooter::BLACK_SCORE_POS{ 290.f,825.f };
const sf::Vector2f GameBoardFooter::WHITE_SCORE_POS{ 430.f,825.f };


GameBoardFooter::GameBoardFooter() :
	GameObject(FOOTER_NAME, FOOTER_POS, FOOTER_SIZE),
	black_score(BLACK_SCORE_POS),
	white_score(WHITE_SCORE_POS),
	settingsButton(SETTINGS_BUTTON_NAME, SETTINGS_BUTTON_POS, SETTINGS_BUTTON_SIZE)
{
	addChild(&black_score);
	addChild(&white_score);
	addChild(&settingsButton);

	black_score.update(2);
	white_score.update(2);
}
