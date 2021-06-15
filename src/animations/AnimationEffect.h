#pragma once
#include <SFML/Graphics.hpp>

namespace reversi
{
	bool popup(sf::Sprite* sprite, const float dt);
	bool fade_in(sf::Sprite* sprite, const float dt);
	bool fade_out(sf::Sprite* sprite, const float dt);
	bool none(sf::Sprite* sprite, const float dt);
}