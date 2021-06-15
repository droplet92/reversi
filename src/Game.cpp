#include "Game.h"
#include "states/TitleState.h"
#include "utilities/Timer.h"
#include <cassert>

using namespace reversi;

const sf::Vector2u Game::WINDOW_SIZE{ 800,900 };
const std::string Game::WINDOW_TITLE = "reversi";

constexpr uint32_t FRAME_PER_SECOND = 60u;
constexpr float MS_PER_FRAME = 16.0f;


Game::Game() : // sf::Style::Close gives the window fixed size
	window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, sf::Style::Close),
	bgm(Jukebox::SOUND_BACKGROUND),
	state(nullptr)
{
	/* window settings */
	sf::Image icon;
	if (!icon.loadFromFile(GameObject::IMAGE_PREFIX + "icon" + GameObject::IMAGE_SUFFIX))
		assert(!"Failed to load the icon.png");

	const uint8_t* pixels = icon.getPixelsPtr();
	window.setIcon(50, 50, pixels);
	window.setFramerateLimit(FRAME_PER_SECOND);

	changeState(new TitleState(this));

	auto& settings = footer.getSettingsButton().getPopup();
	bgm.randomPlay();
	settings.registerBGM(bgm);
	settings.registerAiDifficultyManager(playerManager);
}

Game::~Game()
{
	delete state;
}

void Game::run()
{
	sf::Event event;
	Timer timer;

	while (window.isOpen())
	{
		timer.record();

		processInput(event);
		while (timer.getDelay() >= MS_PER_FRAME)
		{
			update(timer.getTick());
			timer.updateDelay(-MS_PER_FRAME);
		}
		render();
	}
}

void Game::processInput(sf::Event& event)
{
	inputManager.waitEvent();

	while (window.pollEvent(event))
	{
		inputManager.captureEvent(event);

		if (inputManager.windowInput.closed())
			window.close();
	}
}
 
void Game::update(const float dt)
{
	// update layer 0: bgm
	bgm.update();
	
	// update layer 1: settings
	if (footer.getSettingsButton().onClick(inputManager.mouseInput))
		footer.getSettingsButton().pop<GameObject>();

	if (footer.getSettingsButton().onfocus())
	{
		footer.getSettingsButton().getPopup().each([&](SettingOption*& opt) { opt->update(inputManager.mouseInput); });
		return;
	}

	// update layer 2: state
	state->nupdate(inputManager.mouseInput);

	// update layer 3: time objects
	if (!animationManager.nupdate(dt))
		return;

	// update layer 4: event objects
	mouse.update(inputManager.mouseInput);
	state->update(*this, inputManager);
}

void Game::render()
{
	window.clear(sf::Color::White);

	board.drawTo(window);
	footer.drawTo(window);
	animationManager.drawTo(window);
	state->drawTo(window);
	footer.getSettingsButton().getPopup().drawTo(window);

	window.display();
}

void Game::changeState(GameState* _state)
{
	if (state)
	{
		state->exit(*this, inputManager);
		delete state;
	}
	state = _state;
	state->enter(*this);
}
