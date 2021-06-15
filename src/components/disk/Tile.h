#pragma once
#include "../../GameObject.h"
#include "../../types/PlayerType.h"
#include "../../types/Position.h"
#include "../../utilities/minimax/Stone.hpp"

namespace reversi
{
	class Tile : public GameObject, public Stone
	{
	public:
		static const sf::IntRect TILE_SIZE;
		static const std::string BLACK_IMAGE;
		static const std::string WHITE_IMAGE;

		const BoardPosition position;

	private:
		PlayerType owner;

	public:
		Tile(const PlayerType player, const BoardPosition pos);
		~Tile() override {}

		PlayerType getOwner() const { return owner; }

		void changeOwner();

	public:
		int getRow() const final { return position.brow; }
		int getCol() const final { return position.bcol; }
	};
}