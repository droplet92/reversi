#pragma once
#include "GameBoardFooter.h"
#include "../disk/ReversiDisk.h"
#include "../../GameObject.h"
#include "../../types/PlayerType.h"
#include "../../utilities/minimax/Board.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace reversi
{
	constexpr uint32_t BOARD_ROW = 8u;
	constexpr uint32_t BOARD_COL = 8u;
	constexpr uint32_t BOARD_SIZE = BOARD_ROW * BOARD_COL;

	class GameBoard : public GameObject, public Board<8u, 8u>
	{
	public:
		static const std::string IMAGE;
		static const sf::Vector2f POS;
		static const sf::IntRect SIZE;

	private:
		std::shared_ptr<ReversiDisk> board[BOARD_ROW][BOARD_COL];
		std::weak_ptr<ReversiDisk> previous;
		uint32_t ndisk;
		bool _passed;

		std::vector<std::shared_ptr<Tile>> placable;

	public:
		GameBoard();
		~GameBoard() final;

		void init();
		void reset();

		bool onBoard(const Position& pos) const;
		bool canPlace(const Position& pos) const;
		bool isOver() const;
		bool hasNoPlace() const { return placable.empty(); }
		bool passed() const { return _passed; }

		void pass() { _passed = true; }
		void resetpass() { _passed = false; }
		int getCount(const PlayerType player) const { return getDisks(player).size(); }
		[[nodiscard]] std::unique_ptr<std::vector<BoardPosition>> getPlacablePositions() const;

		void highlightPrevious() { previous.lock()->highlightPrevious(); }
		void lightup();
		void lightup(const PlayerType& player, const BoardPosition pos);
		void lightoff();
		void blackout();

		[[nodiscard]] std::weak_ptr<ReversiDisk> placeDisk(const PlayerType& player, const BoardPosition pos);
		void update(std::weak_ptr<ReversiDisk>& disk);
		void updatePlacable(const PlayerType& player);
		void clearPlacables()
		{
			for (auto& tile : placable) tile.reset();
			placable.clear();
		}

		void drawTo(sf::RenderWindow& window) final;

	public:	// for Minimax
		GameBoard(const GameBoard* copy)
		{
			for (int i = 0; i < BOARD_ROW; i++)
				for (int j = 0; j < BOARD_COL; j++)
				{
					ReversiDisk* original = copy->board[i][j].get();
					if (original)
						board[i][j] = std::make_shared<ReversiDisk>(original->getOwner(), original->position);
					else
						board[i][j] = nullptr;
				}
			const BoardPosition& pos = copy->previous.lock()->position;
			previous = board[pos.brow][pos.bcol];

			ndisk = copy->ndisk;
			_passed = copy->_passed;

			for (auto& original : copy->placable)
			{
				Tile* tile = original.get();
				placable.push_back(std::make_shared<Tile>(tile->getOwner(), tile->position));
			}
		}
		std::vector<std::weak_ptr<Stone>> getPlacables() const final
		{
			std::vector<std::weak_ptr<Stone>> placables;
			std::for_each(placable.begin(), placable.end(),
				[&placables](std::weak_ptr<Tile> tile) { placables.push_back(tile); });
			return placables;
		}
		size_t getnumberOfPlacables() const { return getPlacables().size(); }
		uint32_t getScore(const uint32_t playerType) const final { return getCount(static_cast<PlayerType>(playerType)); }
		uint32_t issuperior(const uint32_t playerType) const final
		{
			const PlayerType player = static_cast<PlayerType>(playerType);
			const PlayerType opponent = static_cast<PlayerType>((playerType % 2) + 1);
			return (getCount(player) - getCount(opponent));
		}
		bool isover() const final { return isOver(); }

		void put(const uint32_t type, const Stone& s) final
		{
			const BoardPosition position = { s.getRow(), s.getCol() };
			std::weak_ptr<ReversiDisk> d = placeDisk(static_cast<PlayerType>(type), position);
			update(d);

			if (isOver()) return;
			updatePlacable(static_cast<PlayerType>(type % 2 + 1));

			if (hasNoPlace())	// pass
			{
				updatePlacable(static_cast<PlayerType>(type));
				pass();
				return;
			}
			resetpass();
		}
		void retract(const Stone& s) final
		{
		}

	private:
		void resetColor()
		{
			std::for_each(placable.begin(), placable.end(),
				[](std::shared_ptr<Tile>& tile) {tile->resetColor(); });
		}
		bool isFull() const { return (ndisk == BOARD_SIZE); }

		std::vector<std::weak_ptr<ReversiDisk>> getDisks(const PlayerType player) const;

		void updateDisks(std::weak_ptr<ReversiDisk>& disk);
		void turnOver();
	};
}