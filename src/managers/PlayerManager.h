#pragma once
#include "../animations/GameAnimation.h"
#include "../players/AIPlayer.h"
#include "../players/Player.h"
#include "../players/ai/EasyAI.h"
#include "../players/ai/NormalAI.h"
#include "../players/ai/HardAI.h"
#include "../types/PlayerType.h"

namespace reversi
{
	class PlayerManager
	{
	private:
		GameAnimation _draw;

		GamePlayer* player;
		AIPlayer* ai;
		GamePlayer* turn;	// [point_static]

	public:
		PlayerManager();
		~PlayerManager();

		GamePlayer* getTurnPlayer() { return turn; }
		const GamePlayer* getPlayer() { return player; }
		const AIPlayer* getAI() { return ai; }

		PlayerManager& setPlayer(const PlayerType type)
		{
			delete player;
			player = new Player(type);
			return *this;
		}
		PlayerManager& setAI(const PlayerType type)
		{
			delete ai;
			ai = new AIPlayer(type, new NormalAI(type));
			return *this;
		}

		template <class AI_TYPE>
		void changeAI() { ai->changeAI(new AI_TYPE(ai->type)); }

		void playVoice() { turn->getVoice()->randomPlay(); }
		void startTurn()
		{
			if (player->type == PlayerType::BLACK) turn = player;
			else turn = ai;
		}
		[[nodiscard]] GameAnimation& changeTurn()
		{
			if (turn == player) return (turn = ai)->myTurn();
			return (turn = player)->myTurn();
		}
		[[nodiscard]] GameAnimation& fanfare(const PlayerType winner); // [not_null]
	};
}