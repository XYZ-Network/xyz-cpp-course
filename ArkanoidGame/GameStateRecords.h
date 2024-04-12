#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	class Game;

	struct GameStateRecordsData
	{
		// Resources
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

	void InitGameStateRecords(GameStateRecordsData& data);
	void ShutdownGameStateRecords(GameStateRecordsData& data);
	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, const sf::Event& event);
	void UpdateGameStateRecords(GameStateRecordsData& data, float timeDelta);
	void DrawGameStateRecords(GameStateRecordsData& data, sf::RenderWindow& window);
}
