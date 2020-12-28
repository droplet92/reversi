#include "ReversiDisk.h"
using namespace yothello;

const std::vector<BoardPosition> ReversiDisk::CLOCKWISE_DIRECTION = {
	{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}
};

ReversiDisk::ReversiDisk(const PlayerType player, const BoardPosition pos) :
	Tile(player, pos)
{
	nearest.fill(std::weak_ptr<ReversiDisk>());
}

std::vector<std::shared_ptr<Tile>> ReversiDisk::getPlacables()
{
	std::vector<std::shared_ptr<Tile>> res;
	std::weak_ptr<ReversiDisk> cur, prev;

	for (const auto& dir : CLOCKWISE_DIRECTION)
	{
		cur = getNeighbor(dir);
		prev = std::weak_ptr<ReversiDisk>();

		while (!cur.expired() && (cur.lock()->getOwner() != getOwner()))
		{
			prev = cur;
			cur = cur.lock()->getNeighbor(dir);
		}
		if (!cur.expired()) continue;
		if (!prev.expired() && (prev.lock()->position + dir).inBoundary())
		{
			std::shared_ptr<Tile> tile = std::make_shared<Tile>(getOwner(), prev.lock()->position + dir);
			tile->toTranslucency();
			res.push_back(tile);
		}
	}
	return res;
}

bool ReversiDisk::setNearest(std::weak_ptr<ReversiDisk>& disk)
{
	const BoardPosition& here = position;
	const BoardPosition& there = disk.lock()->position;
	const BoardPosition& direction = there - here;

	if (here.onSide(there))
	{
		const auto res = find(
			CLOCKWISE_DIRECTION.begin(), CLOCKWISE_DIRECTION.end(), direction
		);
		const int index = res - CLOCKWISE_DIRECTION.begin();
		nearest[index] = disk;
		return true;
	}
	return false;
}

void ReversiDisk::updateSelf(std::weak_ptr<ReversiDisk> disk)
{
	const BoardPosition& here = position;
	const BoardPosition& there = disk.lock()->position;
	const BoardPosition direction = there - here;

	if (setNearest(disk))
		turnOver(direction);
}

std::weak_ptr<ReversiDisk> ReversiDisk::getNeighbor(const BoardPosition dir)
{
	const auto res = find(CLOCKWISE_DIRECTION.begin(), CLOCKWISE_DIRECTION.end(), dir);

	if (res == CLOCKWISE_DIRECTION.end())
		return std::weak_ptr<ReversiDisk>();
	int index = res - CLOCKWISE_DIRECTION.begin();
	return nearest[index];
}

std::vector<std::weak_ptr<ReversiDisk>> ReversiDisk::getNeighbors()
{
	std::vector<std::weak_ptr<ReversiDisk>> neighbor;
	std::weak_ptr<ReversiDisk> d;
	neighbor.reserve(CLOCKWISE_DIRECTION.size());

	for (const auto& dir : CLOCKWISE_DIRECTION)
	{
		if (!(d = getNeighbor(dir)).expired())
			neighbor.push_back(d);
	}
	return neighbor;
}

void ReversiDisk::turnOver(const BoardPosition dir)
{
	std::vector<std::weak_ptr<ReversiDisk>> candidateToReverse;
	std::weak_ptr<ReversiDisk> cur = getNeighbor(dir);

	while (!cur.expired() && (cur.lock()->getOwner() != getOwner()))
	{
		candidateToReverse.push_back(cur);
		cur = cur.lock()->getNeighbor(dir);
	}
	if (cur.expired()) return;				// ignore
	for (auto& disk : candidateToReverse)	// execute
		disk.lock()->changeOwner();
}
