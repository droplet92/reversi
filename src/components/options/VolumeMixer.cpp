#include "VolumeMixer.h"
#include "../../popups/Settings.h"
using namespace yothello;

const std::string VolumeMixer::VOLUME_MIXER_NAME = "volume_mixer";
const sf::Vector2f VolumeMixer::BGM_VOLUME_POS{ 100.0f,150.0f };	// component of POPUP
const sf::Vector2f VolumeMixer::VOICE_VOLUME_POS{ 100.0f,180.0f };	// component of POPUP
const sf::IntRect VolumeMixer::VOLUME_MIXER_SIZE{ 0,0,300,5 };

const std::string VolumeMixer::MixerBar::MIXER_BAR_NAME = "mixer_bar";
const sf::Vector2f VolumeMixer::MixerBar::MIXER_BAR_POS{ 90.0f,-7.5f };	// component of VOLUME_MIXER
const sf::IntRect VolumeMixer::MixerBar::MIXER_BAR_SIZE{ 0,0,8,20 };


VolumeMixer::MixerBar::MixerBar(sf::Vector2f pos) :
	GameObject(MIXER_BAR_NAME, (MIXER_BAR_POS + pos), MIXER_BAR_SIZE)
{
}

VolumeMixer::VolumeMixer(sf::Vector2f pos) :
	GameObject(VOLUME_MIXER_NAME, (Settings::SETTINGS_POS + pos), VOLUME_MIXER_SIZE),
	volume(30),
	mixerBar(Settings::SETTINGS_POS + pos)
{
	GameObject::addChild(&mixerBar);
}
