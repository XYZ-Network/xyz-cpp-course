#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	struct Game;

	struct GameStateRecordsData
	{
		// Resources
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	void InitGameStateRecords(GameStateRecordsData& data, Game& game);
	void ShutdownGameStateRecords(GameStateRecordsData& data, Game& game);
	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event);
	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta);
	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window);
}
