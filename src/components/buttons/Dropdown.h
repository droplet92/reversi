#pragma once
#include "../../inputs/MouseInput.h"
#include "GameButton.h"
#include "ToggleButton.h"

namespace yothello
{
	using option_button = std::pair<sf::Text, PlainButton>;

	class DropdownOption : public GameObject
	{
	public:
		static const std::string DEFAULT_SELECTED_TEXT;
		static const std::string DROPDOWN_OPTION_NAME;
		static const sf::Vector2f DROPDOWN_OPTION_POS;
		static const sf::IntRect DROPDOWN_OPTION_SIZE;

	private:
		sf::Text text;

	public:
		DropdownOption(sf::Vector2f pos);
		~DropdownOption() final {}
		void drawTo(sf::RenderWindow& window) final
		{
			window.draw(*this);
			window.draw(text);
		}
		void toTranslucency(const uint8_t alpha = 0x80u) override
		{ text.setFillColor({ 0x00u,0x00u,0x00u,alpha }); GameObject::toTranslucency(alpha); }
		void setInvisible() override { text.setFillColor({ 0x00u,0x00u,0x00u,0x00u }); GameObject::setInvisible(); }
		void changeText(const std::string selected) { text.setString(selected); }
	};

	class Dropdown : public GameObject
	{
	public:
		static const std::string ARRANGE_BUTTON_NAME;
		static const sf::Vector2f ARRANGE_BUTTON_POS;
		static const sf::IntRect ARRANGE_BUTTON_SIZE;

	private:
		DropdownOption selected;
		ToggleButton arrange_button;

		class OptionList : public GameObject
		{
		public:
			static const std::string OPTION_NAME;
			static const sf::Vector2f OPTION_LIST_POS;
			static const sf::IntRect OPTION_SIZE;
			
		private:
			std::vector<option_button> options;

		public:
			OptionList(sf::Vector2f pos, std::vector<std::string> contents);
			~OptionList() {}

			std::string getText(int index) const { return options.at(index).first.getString(); }
			void show_list();
			void hide_list();
			int getIndex(const MouseInput& mouseInput);
			void drawTo(sf::RenderWindow& window) override;
			void close() override;  
		} option_list;

	public:
		Dropdown(sf::Vector2f pos, std::vector<std::string> contents);
		~Dropdown() {}

		bool onToggle() const { return arrange_button.onToggle(); }
		void setSelected(int index) { selected.changeText(option_list.getText(index)); }

		[[nodiscard]] int update(MouseInput& mouseInput);
	};
}