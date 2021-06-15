#pragma once
#include "../../GameObject.h"
#include "../../inputs/MouseInput.h"

namespace reversi
{
	class Mouse : public GameObject
	{
	public:
		static const std::string MOUSE_NAME;
		static const sf::Vector2f MOUSE_POS;
		static const sf::IntRect MOUSE_SIZE;

	public:
		Mouse();
		~Mouse() {}

		void update(const MouseInput& mouseInput);
	};
}