#pragma once
#include "SettingOption.h"
#include "../../utilities/Jukebox.h"
#include "../buttons/GameButton.h"
#include "../buttons/Dropdown.h"
#include <vector>
#include <string>

namespace reversi
{
	class MusicSelector : public Dropdown, public SettingOption
	{
	public:
		static const sf::Vector2f MUSIC_SELECTOR_POS;
		static const std::vector<std::string> MUSIC_LIST;

	private:
		Jukebox* bgm; // [point_static]

	public:
		MusicSelector();
		~MusicSelector() final {}

		void registerMusic(Jukebox* music) { bgm = music; setSelected(music->onplaying()); }

		void update(MouseInput& mouseInput) final
		{
			const int selection = Dropdown::update(mouseInput);
			if (selection >= 0)
				bgm->play(selection);
		}
	};
}