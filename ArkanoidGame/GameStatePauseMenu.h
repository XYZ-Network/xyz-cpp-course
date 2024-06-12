#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePauseMenuData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
	};
}
