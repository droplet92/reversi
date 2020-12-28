#pragma once
#include "SettingOption.h"
#include "../buttons/Dropdown.h"

namespace yothello
{
	class PlayerManager;

	enum class Difficulty
	{
		EASY = 0,
		NORMAL,
		HARD
	};

	class DifficultySelector : public Dropdown, public SettingOption
	{
	public:
		static const sf::Vector2f DIFFICULTY_SELECTOR_POS;
		static const std::vector<std::string> DIFFICULTY_LIST;

	private:
		PlayerManager* playerManager;

	public:
		DifficultySelector();
		~DifficultySelector() final {}

		void registerPlayerManager(PlayerManager& pm);

		void update(MouseInput& mouseInput) final;
	};
}