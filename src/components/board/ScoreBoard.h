#pragma once
#include "../../GameObject.h"
#include <vector>

namespace yothello
{
	class ScoreBoard : public GameObject
	{
	public:
		static const std::vector<int> NUM_XPOS;
		static const int NUM_YPOS;
		static const std::string NUMBER_SHEET_NAME;
		static const sf::IntRect NUMBER_SHEET_SIZE;
		static const sf::IntRect NUM_SIZE;
		static const sf::Vector2f UNITS_GAP;

	private:
		GameObject tens, units;
		int score;

	public:
		ScoreBoard(const sf::Vector2f pos);
		~ScoreBoard() final {}

		int getScore() const { return score; }

		void update(const int score);
	};
}
