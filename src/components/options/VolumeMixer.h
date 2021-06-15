#pragma once
#include "../../GameInterfaces.h"
#include "../../GameObject.h"
#include "SettingOption.h"
#include "../../utilities/Jukebox.h"

namespace reversi
{
	class VolumeMixer : public IComposite<Jukebox>, public SettingOption, public GameObject
	{
	public:
		static const std::string VOLUME_MIXER_NAME;
		static const sf::Vector2f BGM_VOLUME_POS;
		static const sf::Vector2f VOICE_VOLUME_POS;
		static const sf::IntRect VOLUME_MIXER_SIZE;

	private:
		int volume;

		class MixerBar : public GameObject
		{
		public:
			static const std::string MIXER_BAR_NAME;
			static const sf::Vector2f MIXER_BAR_POS;
			static const sf::IntRect MIXER_BAR_SIZE;

			MixerBar(sf::Vector2f pos);
			~MixerBar() final {}
		} mixerBar;

	public:
		VolumeMixer(sf::Vector2f pos);
		~VolumeMixer() final {}

		void update(MouseInput& mouseInput) final
		{
			if (mixerBar.includes(mouseInput.position) && mouseInput.onClick())
				mouseInput.registerListener(&mixerBar);
			else if (mouseInput.onDrag())
			{
				const float inf = getPosition().x;
				const float sup = inf + getLocalBounds().width;
				mouseInput.notifyDrag(inf, sup);
				changeVolume();
			}
		}
		void registerJukebox(Jukebox& jukebox)
		{
			IComposite<Jukebox>::addChild(&jukebox);
			changeVolume();
		}

	private:
		void tune(const int& _volume)
		{
			std::for_each(IComposite<Jukebox>::children.begin(), IComposite<Jukebox>::children.end(),
				[&_volume](Jukebox*& jukebox) { jukebox->tune(_volume); });
		}
		void changeVolume()
		{
			constexpr int PERCENT = 100;
			const float xpos = mixerBar.getPosition().x - getPosition().x;
			volume = static_cast<int>(xpos / VOLUME_MIXER_SIZE.width * PERCENT);
			tune(volume);
		}
	};
}