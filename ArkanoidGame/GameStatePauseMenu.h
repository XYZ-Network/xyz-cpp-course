#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	class Game;

	struct GameStatePauseMenuData
	{
		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
	};

	void InitGameStatePauseMenu(GameStatePauseMenuData& data);
	void ShutdownGameStatePauseMenu(GameStatePauseMenuData& data);
	void HandleGameStatePauseMenuWindowEvent(GameStatePauseMenuData& data, const sf::Event& event);
	void UpdateGameStatePauseMenu(GameStatePauseMenuData& data, float timeDelta);
	void DrawGameStatePauseMenu(GameStatePauseMenuData& data, sf::RenderWindow& window);
}
