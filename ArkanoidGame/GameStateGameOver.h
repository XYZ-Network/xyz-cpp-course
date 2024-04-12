#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	class Game;

	struct GameStateGameOverData
	{
		// Resources
		sf::Font font;

		float timeSinceGameOver = 0.f;

		// UI data
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
	};

	// Returns pointer to the allocated data
	void InitGameStateGameOver(GameStateGameOverData& data);
	void ShutdownGameStateGameOver(GameStateGameOverData& data);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window);
}
