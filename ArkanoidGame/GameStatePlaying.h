#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Snake.h"


namespace SnakeGame
{
	class Game;

	struct GameStatePlayingData
	{
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

	void InitGameStatePlaying(GameStatePlayingData& data);
	void ShutdownGameStatePlaying(GameStatePlayingData& data);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, sf::RenderWindow& window);
}
