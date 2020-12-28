#include "ScoreBoard.h"
using namespace yothello;

const std::vector<int> ScoreBoard::NUM_XPOS = {
	0, 42, 84, 126, 168, 210, 252, 294, 336, 378, 420
};
const int ScoreBoard::NUM_YPOS = 0;
const std::string ScoreBoard::NUMBER_SHEET_NAME = "number";
const sf::IntRect ScoreBoard::NUMBER_SHEET_SIZE{ 0,0,420,50 };
const sf::IntRect ScoreBoard::NUM_SIZE{ 0,0,42,50 };
const sf::Vector2f ScoreBoard::UNITS_GAP{ 40.f,0.f };

namespace RangeClamp
{
	constexpr int getTens(const int& score) { return score / 10; }
	constexpr int getUnits(const int& score) { return score % 10; }
	constexpr int wrap_around(const int x) { return (x - 1 < 0) ? 9 : (x - 1); }
}


ScoreBoard::ScoreBoard(const sf::Vector2f pos) :
	GameObject(pos),
	score(2),
	tens(NUMBER_SHEET_NAME, pos, NUMBER_SHEET_SIZE),
	units(NUMBER_SHEET_NAME, pos + UNITS_GAP, NUMBER_SHEET_SIZE)
{
	addChild(&tens);
	addChild(&units);
}

void ScoreBoard::update(const int _score)
{
	score = _score;
	tens.setTextureRect({
		NUM_XPOS[RangeClamp::wrap_around(RangeClamp::getTens(score))],
		NUM_YPOS,
		NUM_SIZE.width,
		NUM_SIZE.height
	});
	units.setTextureRect({
		NUM_XPOS[RangeClamp::wrap_around(RangeClamp::getUnits(score))],
		NUM_YPOS,
		NUM_SIZE.width,
		NUM_SIZE.height
	});
}
