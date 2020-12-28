#pragma once
#include "GameButton.h"

namespace yothello
{
	class ToggleButton : public PlainButton
	{
	private:
		bool on_toggle;

	public:
		ToggleButton(const std::string imagename, const sf::Vector2f pos, const sf::IntRect size, const bool default_toggle = false) :
			PlainButton(imagename, pos, size),
			on_toggle(default_toggle)
		{
		}
		~ToggleButton() final
		{
		}

		bool onToggle() const { return on_toggle; }
		bool onClick(const MouseInput& mouseInput) final
		{
			if (PlainButton::onClick(mouseInput))
			{
				toggle();
				return true;
			}
			return false;
		}

	private:
		void toggle() { on_toggle = !on_toggle; }
	};
}