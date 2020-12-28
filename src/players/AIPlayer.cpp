#include "AIPlayer.h"
#include "../components/board/GameBoard.h"
using namespace yothello;

const std::string AIPlayer::LOADING_IMAGE = "loading";
const sf::Vector2f AIPlayer::BLACK_LOADING_POS{ 70.f,812.5f };
const sf::Vector2f AIPlayer::WHITE_LOADING_POS{ 640.f,812.5f };
const sf::IntRect AIPlayer::LOADING_SIZE{ 0,0,75,75 };
const uint32_t AIPlayer::LOADING_FRAME = 10u;
const uint8_t AIPlayer::LOADING_ALPHA = 0xFFu;


AIPlayer::AIPlayer(const PlayerType type, GameAI* ai) :
	GamePlayer(
		type,
		new GameAnimation{
			LOADING_IMAGE,
			(type == PlayerType::BLACK) ? BLACK_LOADING_POS : WHITE_LOADING_POS,
			LOADING_SIZE,
			LOADING_FRAME,
			GameAnimation::EXPIRES,
			none,
			LOADING_ALPHA
		}
	),
	ai(ai),
	future(nullptr)
{
	ai->printDifficulty();
}

AIPlayer::~AIPlayer()
{
	delete ai;
	delete future;
}

void AIPlayer::init()
{
	delete future;
	future = nullptr;
}

Decision AIPlayer::awaitDecision(GameBoard& board, const MouseInput&)
{
	if (!future)
	{
		future = new std::future<BoardPosition>(std::async(std::launch::async, [&] { return ai->makeDicision(board); }));
	}
	if (future->wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		const BoardPosition pos = future->get();
		delete future;
		future = nullptr;
		return Decision(pos);
	}
	return Decision();
}
