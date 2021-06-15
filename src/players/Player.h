#pragma once
#include "../GamePlayer.h"
#include "../types/Decision.h"
#include "../types/PlayerType.h"
#include "../inputs/MouseInput.h"

namespace reversi
{
	class Player : public GamePlayer
	{
	public:
		Player(const PlayerType type);
		~Player() final {}

		Decision awaitDecision(GameBoard& board, const MouseInput& mouseInput) final;
	};
}