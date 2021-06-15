#include "PlayState.h"
#include "EndState.h"
#include "../Game.h"
#include "../animations/AnimationEffect.h"
#include "../managers/AnimationManager.h"
#include "../managers/InputManager.h"
using namespace reversi;

namespace BoardFunctions
{
	void placeDisk(const BoardPosition position, Game& game)
	{
		auto& board = game.getBoard();
		auto turnPlayer = game.getPlayerManager().getTurnPlayer();

		std::weak_ptr<ReversiDisk> d = board.placeDisk(turnPlayer->type, position);
		board.update(d);
		game.getFooter().updateScore(board.getCount(PlayerType::BLACK), board.getCount(PlayerType::WHITE));
		turnPlayer->getVoice()->randomPlay();
	}

	void nextTurn(Game& game)
	{
		GameAnimation& change_turn_animation = game.getPlayerManager().changeTurn();

		game.getAnimationManager().push(change_turn_animation);
		game.getBoard().updatePlacable(game.getPlayerManager().getTurnPlayer()->type);
	}
}


PlayState::PlayState(Game* game) :
	GameState(game),
	_pass(GameAnimation::PASS_NAME, GameAnimation::ANIMATION_POS_BIG, GameAnimation::NOT_EXPIRES, popup)
{
}

void PlayState::exit(Game& game)
{
	game.getAnimationManager().stop();
}

void PlayState::update(Game& game, InputManager& inputManager)
{
	auto& settings = game.getFooter().getSettingsButton().getPopup();
	if (game.over()) return;

	GameBoard& board = game.getBoard();
	board.lightoff();

	const auto decision = game.getPlayerManager().getTurnPlayer()->awaitDecision(board, inputManager.mouseInput);
	if (!decision.ready)
	{
		game.getAnimationManager().stop();
		auto& turnAnimation = game.getPlayerManager().getTurnPlayer()->myTurn();
		game.getAnimationManager().push(turnAnimation);
		return;
	}
	Logger::instance().write(std::to_string(static_cast<int>(game.getPlayerManager().getTurnPlayer()->type))
							+ decision.bposition.toString());
	BoardFunctions::placeDisk(decision.bposition, game);

	if (board.isOver()) return;
	BoardFunctions::nextTurn(game);

	if (board.hasNoPlace())	// pass
	{
		Logger::instance().write("JUMPS");
		game.getAnimationManager().push(_pass);
		BoardFunctions::nextTurn(game);
		board.pass();
		return;
	}
	board.resetpass();
}

void PlayState::nupdate(const MouseInput& mouseInput)
{
	if (owner->over())
		owner->changeState(new EndState(owner));
}
