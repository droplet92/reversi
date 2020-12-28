#pragma once
#include "Dropdown.h"
#include <cassert>
using namespace yothello;

const std::string DropdownOption::DEFAULT_SELECTED_TEXT = "NONE";
const std::string DropdownOption::DROPDOWN_OPTION_NAME = "dropdown_option";
const sf::Vector2f DropdownOption::DROPDOWN_OPTION_POS{ 0.0f,0.0f };
const sf::IntRect DropdownOption::DROPDOWN_OPTION_SIZE{ 0,0,300,25 };

const std::string Dropdown::OptionList::OPTION_NAME = /*"option"*/ "volume_mixer";
const sf::Vector2f Dropdown::OptionList::OPTION_LIST_POS{ 100.0f,300.0f };
const sf::IntRect Dropdown::OptionList::OPTION_SIZE{ 0,0,300,25 };

const std::string Dropdown::ARRANGE_BUTTON_NAME = "arrange_button";
const sf::Vector2f Dropdown::ARRANGE_BUTTON_POS{ 300.0f,0.0f };
const sf::IntRect Dropdown::ARRANGE_BUTTON_SIZE{ 0,0,25,25 };

DropdownOption::DropdownOption(sf::Vector2f pos) :
	GameObject(DROPDOWN_OPTION_NAME, pos + DROPDOWN_OPTION_POS, DROPDOWN_OPTION_SIZE)
{
	static sf::Font font;
	if (!font.loadFromFile("resources/dovemayo.otf"))
		assert(!"Failed to load the font file");
	text.setFont(font);
	text.setString(DEFAULT_SELECTED_TEXT);
	text.setFillColor({ 0x00u,0x00u,0x00u,0x00u });
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setPosition(pos + DROPDOWN_OPTION_POS + sf::Vector2f{ 5.0f,0.0f });
}


Dropdown::Dropdown(sf::Vector2f pos, std::vector<std::string> contents) :
	GameObject(pos),
	selected(pos),
	arrange_button(Dropdown::ARRANGE_BUTTON_NAME, pos + ARRANGE_BUTTON_POS, Dropdown::ARRANGE_BUTTON_SIZE),
	option_list(pos, contents)
{
	addChild(&selected);
	addChild(&arrange_button);
	addChild(&option_list);
}

int Dropdown::update(MouseInput& mouseInput)
{
	if (arrange_button.onClick(mouseInput))
		arrange_button.onToggle() ? option_list.show_list() : option_list.hide_list();
	const int idx = option_list.getIndex(mouseInput);
	if (idx > 0)
	{
		selected.changeText(option_list.getText(idx - 1));
		
		option_list.close();
	}
	return idx;
}

Dropdown::OptionList::OptionList(sf::Vector2f pos, std::vector<std::string> contents) :GameObject(OPTION_LIST_POS)
{
	for (auto iter = contents.begin(); iter != contents.end(); ++iter)
	{
		const float idx = static_cast<float>(iter - contents.begin() + 1);
		sf::Text* text = new sf::Text();
		sf::Font* font = new sf::Font();
		if (!font->loadFromFile("resources/dovemayo.otf"))
			assert(!"Failed to load the font file");
		text->setFont(*font);
		text->setString(*iter);
		text->setFillColor({ 0x00u,0x00u,0x00u,0x00u });
		text->setCharacterSize(20);
		text->setPosition(pos + sf::Vector2f{ 0.0f,25.0f * idx } +sf::Vector2f{ 5.0f,0.0f });

		PlainButton p("dropdown_option", pos + sf::Vector2f{ 0.0f,25.0f * idx }, { 0,0,300,25 });
		p.setUnavailable();

		options.emplace_back(*text, p);
	}
	hide_list();
}

void Dropdown::OptionList::show_list()
{
	for (auto& opt : options)
	{
		opt.first.setFillColor(sf::Color::Black);
		opt.second.setAvailable();
	}
}

void Dropdown::OptionList::hide_list()
{
	for (auto& opt : options)
	{
		opt.first.setFillColor({ 0x00u,0x00u,0x00u,0x00u });
		opt.second.setUnavailable();
	}
}

int Dropdown::OptionList::getIndex(const MouseInput& mouseInput)
{
	option_button const* selected = nullptr;

	for (option_button& opt : options)
		if (opt.second.isAvailable() && opt.second.onClick(mouseInput))
		{
			selected = &opt;
			break;
		}
	return selected ? (selected - (&*options.begin()) + 1) : -1;
}

void Dropdown::OptionList::drawTo(sf::RenderWindow& window)
{
	window.draw(*this);
	for (auto& opt : options)
	{
		opt.second.drawTo(window);
		window.draw(opt.first);
	}
}

void Dropdown::OptionList::close()
{
	GameObject::close();
	hide_list();
}
