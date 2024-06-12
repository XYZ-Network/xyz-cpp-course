#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	class Game;

	class GameStateRecordsData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		// Resources
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};
}
