#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Snake.h"


namespace SnakeGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		// Resources
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		Snake snake;
		sf::Sprite apple;
		std::vector<sf::Sprite> rocks;
		int numEatenApples = 0;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
	};
}
