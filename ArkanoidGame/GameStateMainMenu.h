#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace SnakeGame
{
	class Game;

	struct GameStateMainMenuData
	{
		sf::Font font;
		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window);
}
