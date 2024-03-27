#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePauseMenuData
	{
		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
		MenuItem resumeItem;
		MenuItem exitItem;
	};

	void InitGameStatePauseMenu(GameStatePauseMenuData& data, Game& game);
	void ShutdownGameStatePauseMenu(GameStatePauseMenuData& data, Game& game);
	void HandleGameStatePauseMenuWindowEvent(GameStatePauseMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePauseMenu(GameStatePauseMenuData& data, Game& game, float timeDelta);
	void DrawGameStatePauseMenu(GameStatePauseMenuData& data, Game& game, sf::RenderWindow& window);
}
