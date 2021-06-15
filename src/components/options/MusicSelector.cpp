#include "MusicSelector.h"
#include "../../popups/Settings.h"
using namespace reversi;

const sf::Vector2f MusicSelector::MUSIC_SELECTOR_POS{ 100.0f,300.0f };	// component of POPUP
const std::vector<std::string> MusicSelector::MUSIC_LIST{
	"BGM 1",
	"BGM 2",
	"BGM 3",
	"BGM 4",
	"BGM 5",
	"BGM 6",
	"BGM 7",
	"BGM 8"
};


MusicSelector::MusicSelector() :
	Dropdown(MUSIC_SELECTOR_POS + Settings::SETTINGS_POS, MusicSelector::MUSIC_LIST),
	bgm(nullptr)
{
}
