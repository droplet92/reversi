#include "Settings.h"
#include "../managers/PlayerManager.h"
#include <memory>
using namespace reversi;

const std::string Settings::SETTINGS_NAME = "settings";
const sf::Vector2f Settings::SETTINGS_POS{ 150.0f,50.0f };
const sf::IntRect Settings::SETTINGS_SIZE{ 0,0,500,700 };
const uint8_t Settings::SETTINGS_ALPHA = 0xC0u;

Settings::Settings() :
	GameObject(SETTINGS_NAME, SETTINGS_POS, SETTINGS_SIZE),
	bgmVolume(VolumeMixer::BGM_VOLUME_POS),
	voiceVolume(VolumeMixer::VOICE_VOLUME_POS),
	bgmSelector(),
	difficultySelector()
{
	options.push_back(&bgmVolume);
	options.push_back(&voiceVolume);
	options.push_back(&bgmSelector);
	options.push_back(&difficultySelector);
	addChild(&bgmVolume);
	addChild(&voiceVolume);
	addChild(&difficultySelector); // draw prior to bgmSelector
	addChild(&bgmSelector);
	close();
}

void reversi::Settings::registerAiDifficultyManager(PlayerManager& pm)
{
	difficultySelector.registerPlayerManager(pm);
}
