#include "GameBoard.h"
#pragma warning(disable:4996)
using namespace reversi;

const std::string GameBoard::IMAGE = "board";
const sf::Vector2f GameBoard::POS{ 0.f,0.f };
const sf::IntRect GameBoard::SIZE{ 0,0,800,800 };


namespace TurnOverDisks
{
	bool hasStraightVector(const BoardPosition& dir)
	{
		if (!dir.brow) return true;
		if (!dir.bcol) return true;
		if (dir.brow == dir.bcol) return true;
		if (dir.brow == -dir.bcol) return true;
		return false;
	}

	void previewUpdate(std::shared_ptr<ReversiDisk>(&board)[BOARD_ROW][BOARD_COL], std::vector<std::weak_ptr<ReversiDisk>> v, const BoardPosition pos)
	{
		std::vector<std::weak_ptr<ReversiDisk>> candidates;
		std::weak_ptr<ReversiDisk> d;
		BoardPosition i;

		for (auto& disk : v)
		{
			const BoardPosition& dir = disk.lock()->position - pos;

			if (hasStraightVector(dir))
			{
				for (i = (dir.unit() + pos); (i != disk.lock()->position); i += dir.unit())
				{
					if ((d = board[i.brow][i.bcol]).expired()) break;
					if (d.lock()->getOwner() == disk.lock()->getOwner()) break;
					candidates.push_back(d);
				}
				if (i == disk.lock()->position)
					std::for_each(candidates.begin(), candidates.end(),
						[](std::weak_ptr<ReversiDisk> disk) { disk.lock()->highlight(); });
				candidates.clear();
			}
		}
	}

	[[deprecated("this function will be deleted the next commit")]]
	void turnOver(std::vector<std::weak_ptr<ReversiDisk>>& from, std::vector<std::weak_ptr<ReversiDisk>>& to, const PlayerType player)
	{
		std::copy_if(from.begin(), from.end(), std::back_inserter(to),
			[&player](const std::weak_ptr<ReversiDisk>& disk) { return (disk.lock()->getOwner() == player); });

		from.erase(
			remove_if(from.begin(), from.end(),
				[&player](const std::weak_ptr<ReversiDisk>& disk) { return (disk.lock()->getOwner() == player); }),
			from.end()
		);
	}

	void turnOver(std::shared_ptr<ReversiDisk>(&board)[BOARD_ROW][BOARD_COL], const PlayerType player)
	{
		//for (int i = 0; i < BOARD_ROW; i++)
		//	for (int j = 0; j < BOARD_COL; j++)
		//		if (board[i][j])
		//			;
	}
}


GameBoard::GameBoard() :
	GameObject(GameBoard::IMAGE, GameBoard::POS, GameBoard::SIZE),
	board(),
	ndisk(0),
	_passed(false)
{
}

GameBoard::~GameBoard()
{
	reset();
}

void GameBoard::init()
{
	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			board[i][j] = nullptr;
	placable.reserve(BOARD_ROW * BOARD_COL);

	const std::vector<BoardPosition> initpos = {
		{ 3,4 }, { 3,3 }, { 4,3 }, { 4,4 }
	};
	PlayerType player = PlayerType::BLACK;
	std::weak_ptr<ReversiDisk> d;

	for (auto pos : initpos)
	{
		d = placeDisk(player, pos);
		update(d);
		player = (player == PlayerType::BLACK) ? PlayerType::WHITE : PlayerType::BLACK;
	}
	updatePlacable(PlayerType::BLACK);
	blackout();
}

void GameBoard::reset()
{
	clearPlacables();

	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			if (board[i][j])
				board[i][j].reset();
	ndisk = 0u;
}

bool GameBoard::onBoard(const Position& pos) const
{
	if (!includes(pos)) return false;
	const BoardPosition bpos = pos.toBoardPosition();
	return (board[bpos.brow][bpos.bcol] != nullptr);
}

bool GameBoard::canPlace(const Position& pos) const
{
	if (onBoard(pos)) return false;
	const BoardPosition bpos = pos.toBoardPosition();

	return (placable.end() != find_if(placable.begin(), placable.end(),
		[&bpos](const std::shared_ptr<Tile>& tile) { return (bpos == tile->position); }));
}

bool GameBoard::isOver() const
{
	if (isFull()) return true;
	if (!getCount(PlayerType::BLACK)) return true;
	if (!getCount(PlayerType::WHITE)) return true;
	if (passed() && hasNoPlace()) return true;
	return false;
}

std::unique_ptr<std::vector<BoardPosition>> GameBoard::getPlacablePositions() const
{
	std::vector<BoardPosition> res;
	res.reserve(placable.size());

	for (const auto& p : placable)
		res.push_back(p->position);
	return std::make_unique<std::vector<BoardPosition>>(res);
}

void GameBoard::lightup()
{
	GameObject::resetColor();

	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			if (board[i][j])
				board[i][j]->resetColor();
}

void GameBoard::lightup(const PlayerType& player, const BoardPosition pos)
{
	auto cur = std::find_if(placable.begin(), placable.end(),
		[&pos](const std::shared_ptr<Tile>& tile) { return (pos == tile->position); });
	(*cur)->setBright();
	TurnOverDisks::previewUpdate(board, getDisks(player), pos);
}

void GameBoard::lightoff()
{
	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			if (board[i][j])
				board[i][j]->resetColor();
	for (auto& tile : placable)
		tile->toTranslucency();
}

void GameBoard::blackout()
{
	setDark();
	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			if (board[i][j])
				board[i][j]->setDark();
}

std::weak_ptr<ReversiDisk> GameBoard::placeDisk(const PlayerType& player, const BoardPosition pos)
{
	std::shared_ptr<ReversiDisk> disk = std::make_shared<ReversiDisk>(player, pos);
	previous = (board[pos.brow][pos.bcol] = disk);
	++ndisk;
	return disk;
}

void GameBoard::update(std::weak_ptr<ReversiDisk>& disk)
{
	updateDisks(disk);
	resetColor();
	turnOver();
}

void GameBoard::updatePlacable(const PlayerType& player)
{
	for (auto& tile : placable) tile.reset();
	placable.clear();

	std::vector<std::weak_ptr<ReversiDisk>> onboards = getDisks(player);
	std::vector<std::shared_ptr<Tile>> placables;

	for (auto& disk : onboards)
	{
		placables = disk.lock()->getPlacables();
		for (const auto& tile : placables)
			if (placable.end() == std::find_if(placable.begin(), placable.end(),
				[&tile](const std::shared_ptr<Tile>& p) { return (p->position == tile->position); }))
			{
				placable.push_back(tile);
			}
	}
}

void GameBoard::drawTo(sf::RenderWindow& window)
{
	GameObject::drawTo(window);

	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			if (board[i][j])
				board[i][j]->drawTo(window);
	for (auto& tile : placable)
		tile->drawTo(window);
}

std::vector<std::weak_ptr<ReversiDisk>> GameBoard::getDisks(const PlayerType player) const
{
	std::vector<std::weak_ptr<ReversiDisk>> disks;
	disks.reserve(ndisk);

	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
		{
			if (board[i][j] && (board[i][j]->getOwner() == player))
				disks.push_back(board[i][j]);
		}
	return disks;
}

void GameBoard::updateDisks(std::weak_ptr<ReversiDisk>& disk)
{
	for (int i = 0; (i < BOARD_ROW); i++)
		for (int j = 0; (j < BOARD_COL); j++)
			if (board[i][j])
			{
				disk.lock()->updateSelf(board[i][j]);
				board[i][j]->setNearest(disk);
			}
}

void GameBoard::turnOver()
{
	auto black_disks = getDisks(PlayerType::BLACK);
	auto white_disks = getDisks(PlayerType::WHITE);
							/* from,		to,				which player	*/
	TurnOverDisks::turnOver(black_disks, white_disks, PlayerType::WHITE);
	TurnOverDisks::turnOver(white_disks, black_disks, PlayerType::BLACK);
}

