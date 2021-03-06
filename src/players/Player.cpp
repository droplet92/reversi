#include "Player.h"
#include "../components/board/GameBoard.h"

using namespace reversi;


Player::Player(const PlayerType type) :
	GamePlayer(type, new NullAnimation())
{
}

Decision Player::awaitDecision(GameBoard& board, const MouseInput& mouseInput)
{
	if (mouseInput.onClick())
	{
		if (board.canPlace(mouseInput.position))
			return Decision(mouseInput.position.toBoardPosition());

		if (!board.isOver() && board.onBoard(mouseInput.position))
		{
			return Decision();
		}
	}
	if (!board.passed())	// if the mouse on popup, here is not reached
		board.highlightPrevious();

	if (!mouseInput.onClick())
	{
		if (board.canPlace(mouseInput.position))
			board.lightup(type, mouseInput.position.toBoardPosition());
	}
	return Decision();
}
