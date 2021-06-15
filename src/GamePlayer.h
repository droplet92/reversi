#pragma once
#include "animations/GameAnimation.h"
#include "types/Decision.h"
#include "types/PlayerType.h"
#include "utilities/Jukebox.h"

namespace reversi
{
	class GameBoard;
	class MouseInput;

	class GamePlayer
	{
	public:
		static const std::string FANFARE_SUFFIX;

		GameAnimation fanfare_animation;
		const PlayerType type;

	private:
		GameAnimation* loading;
		Jukebox* voice;

	public:
		GamePlayer(const PlayerType type, GameAnimation* _loading);
		virtual ~GamePlayer();

		Jukebox* getVoice() const { return voice; }

		[[nodiscard]] GameAnimation& myTurn() { return *loading; }
		virtual Decision awaitDecision(GameBoard& board, const MouseInput& mouseInput) = 0;
	};
}