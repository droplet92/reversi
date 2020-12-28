#pragma once
#include "Tile.h"
#include <array>
#include <memory>

namespace yothello
{
	constexpr int NEAREST_LEN = 8;

	class ReversiDisk : public Tile
	{
	public:
		static const std::vector<BoardPosition> CLOCKWISE_DIRECTION;

	private:
		std::array<std::weak_ptr<ReversiDisk>, NEAREST_LEN> nearest;

	public:
		ReversiDisk(const PlayerType player, const BoardPosition pos);
		~ReversiDisk() final {}

		[[nodiscard]] std::vector<std::shared_ptr<Tile>> getPlacables();
		bool setNearest(std::weak_ptr<ReversiDisk>& disk);

		void updateSelf(std::weak_ptr<ReversiDisk> disk);

	private:
		std::weak_ptr<ReversiDisk> getNeighbor(const BoardPosition dir);
		std::vector<std::weak_ptr<ReversiDisk>> getNeighbors();

		void turnOver(const BoardPosition dir);
	};
}