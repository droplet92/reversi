#include "Mouse.h"
using namespace reversi;

const std::string Mouse::MOUSE_NAME = "mouse";
const sf::Vector2f Mouse::MOUSE_POS{ 0.0f,0.0f };
const sf::IntRect Mouse::MOUSE_SIZE{ 0,0,20,20 };


Mouse::Mouse() :
	GameObject()
{
}

void Mouse::update(const MouseInput& mouseInput)
{
	moveTo(mouseInput.position.toVector2D());
}
