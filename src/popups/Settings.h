#pragma once
#include "../GameObject.h"
#include "../components/options/VolumeMixer.h"
#include "../components/options/MusicSelector.h"
#include "../components/options/DifficultySelector.h"
#include "../utilities/Jukebox.h"
#include "../inputs/MouseInput.h"
#include <functional>
#include <list>

namespace yothello
{
	class Settings : public GameObject
	{
	public:
		static const std::string SETTINGS_NAME;
		static const sf::Vector2f SETTINGS_POS;
		static const sf::IntRect SETTINGS_SIZE;
		static const uint8_t SETTINGS_ALPHA;

	private:
		std::list<SettingOption*> options;
		VolumeMixer bgmVolume;
		VolumeMixer voiceVolume;
		MusicSelector bgmSelector;
		DifficultySelector difficultySelector;

	public:
		Settings();
		~Settings() final {}

		bool onMouse(const MouseInput& mouseInput) const { return (visible() && includes(mouseInput.position)); }

		void changeMusic() {}
		void update() {}

		void registerBGM(Jukebox& bgm)
		{
			bgmVolume.registerJukebox(bgm);
			bgmSelector.registerMusic(&bgm);
		}
		void registerVoice(Jukebox& voice)
		{
			voiceVolume.registerJukebox(voice);
		}
		void registerAiDifficultyManager(PlayerManager& pm);

		void clearVoice()
		{
			voiceVolume.IComposite<Jukebox>::clear();
		}

		void each(const std::function<void(SettingOption*&)> f)
		{
			std::for_each(options.begin(), options.end(), [&](SettingOption*& opt) { f(opt); });
		}
	};
}