#include "DifficultySelector.h"
#include "../../popups/Settings.h"
#include "../../managers/PlayerManager.h"
#include "../../players/ai/EasyAI.h"
#include "../../players/ai/NormalAI.h"
#include "../../players/ai/HardAI.h"
using namespace yothello;

const sf::Vector2f DifficultySelector::DIFFICULTY_SELECTOR_POS{ 100.0f,450.0f };	// component of POPUP
const std::vector<std::string> DifficultySelector::DIFFICULTY_LIST{
	"easy",
	"normal",
	"hard"
};


DifficultySelector::DifficultySelector() :
	Dropdown(DIFFICULTY_SELECTOR_POS + Settings::SETTINGS_POS, DifficultySelector::DIFFICULTY_LIST),
	playerManager(nullptr)
{
}

void yothello::DifficultySelector::registerPlayerManager(PlayerManager& pm)
{
	playerManager = &pm;
	setSelected(static_cast<int>(Difficulty::NORMAL));	// default is Normal
}

void yothello::DifficultySelector::update(MouseInput& mouseInput)
{
	const int selection = Dropdown::update(mouseInput);
	
	switch (Difficulty(selection))
	{
	case Difficulty::EASY:		playerManager->changeAI<EasyAI>();		break;
	case Difficulty::NORMAL:	playerManager->changeAI<NormalAI>();	break;
	case Difficulty::HARD:		playerManager->changeAI<HardAI>();		break;
	}
}
