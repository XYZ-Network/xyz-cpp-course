#include "GameStatePlaying.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{	
		// Init game resources (terminate if error)
		LoadSnakeTextures(data.snake);
		assert(data.appleTexture.loadFromFile(TEXTURES_PATH + "Apple.png"));
		assert(data.rockTexture.loadFromFile(TEXTURES_PATH + "Rock.png"));
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(data.eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"));
		assert(data.gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		data.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		data.background.setPosition(0.f, 0.f);
		data.background.setFillColor(sf::Color(0, 200, 0));

		// Init snake
		InitSnake(data.snake);

		// Init apple
		InitSprite(data.apple, APPLE_SIZE, APPLE_SIZE, data.appleTexture);
		SetSpriteRandomPosition(data.apple, data.background.getGlobalBounds(), data.snake.body);

		// Init rocks
		data.rocks.resize(ROCKS_COUNT);
		for (sf::Sprite& rock : data.rocks) {
			InitSprite(rock, ROCK_SIZE, ROCK_SIZE, data.rockTexture);
			SetSpriteRandomPosition(rock, data.background.getGlobalBounds(), data.snake.body);
		}

		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to pause");
		data.inputHintText.setOrigin(GetTextOrigin(data.inputHintText, { 1.f, 0.f }));

		// Init sounds
		data.eatAppleSound.setBuffer(data.eatAppleSoundBuffer);
		data.gameOverSound.setBuffer(data.gameOverSoundBuffer);
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			data.snake.direction = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			data.snake.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			data.snake.direction = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			data.snake.direction = SnakeDirection::Left;
		}

		// Update snake
		MoveSnake(data.snake, timeDelta);

		if (CheckSpriteIntersection(*data.snake.head, data.apple)) {
			data.eatAppleSound.play();

			GrowSnake(data.snake);

			// Increase eaten apples counter
			data.numEatenApples++;
			
			// Move apple to a new random position
			SetSpriteRandomPosition(data.apple, data.background.getGlobalBounds(), data.snake.body);

			// Increase snake speed
			if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration) {
				data.snake.speed += ACCELERATION;
			}
		}

		bool isGameFinished = !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);
		
		if (isGameFinished
			|| !HasSnakeCollisionWithRect(data.snake, data.background.getGlobalBounds()) // Check collision with screen border
			|| CheckSnakeCollisionWithHimself(data.snake)		// Check collision with screen border
			|| FullCheckCollisions(data.rocks.begin(), data.rocks.end(), *data.snake.head)) // Check collision with rocks
		{
			data.gameOverSound.play();

			// Find snake in records table and update his score
			game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME], data.numEatenApples);

			PushGameState(game, GameStateType::GameOver, false);
		}

		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Draw background
		window.draw(data.background);

		// Draw snake
		DrawSnake(data.snake, window);
		// Draw apples
		DrawSprite(data.apple, window);
		// Draw rocks
		DrawSprites(data.rocks.begin(), data.rocks.end(), window);

		data.scoreText.setOrigin(GetTextOrigin(data.scoreText, { 0.f, 0.f }));
		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}
