#pragma once
#include "ScoreBoard.h"
#include "../buttons/GameButton.h"
#include "../../popups/Settings.h"
#include "../../GameObject.h"
#include "../../types/PlayerType.h"

namespace reversi
{
	class GameBoardFooter : public GameObject
	{
	public:
		static const std::string FOOTER_NAME;
		static const sf::Vector2f FOOTER_POS;
		static const sf::IntRect FOOTER_SIZE;

		static const std::string SETTINGS_BUTTON_NAME;
		static const sf::Vector2f SETTINGS_BUTTON_POS;
		static const sf::IntRect SETTINGS_BUTTON_SIZE;

		static const sf::Vector2f BLACK_SCORE_POS;
		static const sf::Vector2f WHITE_SCORE_POS;

	private:
		PopupButton<Settings> settingsButton;
		ScoreBoard black_score;
		ScoreBoard white_score;

	public:
		GameBoardFooter();
		~GameBoardFooter() {}

		PopupButton<Settings>& getSettingsButton() { return settingsButton; }
		int getScore(const PlayerType& player) const { return ((player == PlayerType::BLACK) ? black_score : white_score).getScore(); }

		void updateScore(const int nblack, const int nwhite)
		{
			black_score.update(nblack);
			white_score.update(nwhite);
		}
	};
}