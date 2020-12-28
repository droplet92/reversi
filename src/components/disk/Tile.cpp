#include "Tile.h"
#include <cassert>
using namespace yothello;

const sf::IntRect Tile::TILE_SIZE{ 0, 0, 100, 100 };
const std::string Tile::BLACK_IMAGE = "black";
const std::string Tile::WHITE_IMAGE = "white";


yothello::Tile::Tile(const PlayerType player, const BoardPosition pos) :
	GameObject(
		(player == PlayerType::BLACK) ? BLACK_IMAGE : WHITE_IMAGE,
		sf::Vector2f((float)pos.brow* TILE_SIZE.width, (float)pos.bcol* TILE_SIZE.height),
		TILE_SIZE
	),
	owner(player),
	position(pos)
{
}

void Tile::changeOwner()
{
	if (owner == PlayerType::BLACK)
	{
		owner = PlayerType::WHITE;
		changeTexture(WHITE_IMAGE, TILE_SIZE);
	}
	else if (owner == PlayerType::WHITE)
	{
		owner = PlayerType::BLACK;
		changeTexture(BLACK_IMAGE, TILE_SIZE);
	}
	else
		assert(!"Invalid tile owner");
}
