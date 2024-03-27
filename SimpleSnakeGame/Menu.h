#pragma once
#include "SFML/Graphics.hpp"
#include "Text.h"
#include <list>

namespace SnakeGame
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; // Visible when child item is selected
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing;

		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;

		bool isEnabled = true;
		std::vector<MenuItem*> children;

		MenuItem* parent = nullptr;
	};

	struct Menu
	{
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	};

	// Links children to parent
	void InitMenuItem(MenuItem& menu);
	void SelectMenuItem(Menu& menu, MenuItem* item);
	bool SelectPreviousMenuItem(Menu& menu);
	bool SelectNextMenuItem(Menu& menu);
	bool ExpandSelectedItem(Menu& menu);
	bool CollapseSelectedItem(Menu& menu);

	MenuItem* GetCurrentMenuContext(Menu& menu);

	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
}
