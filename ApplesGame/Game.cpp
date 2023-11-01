#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	void RestartGame(Game& game)
	{
		SetPlayerPosition(game.player, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		SetPlayerSpeed(game.player, INITIAL_SPEED);
		SetPlayerDirection(game.player, PlayerDirection::Right);

		// Init apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			SetApplePosition(game.apples[i], GetRandomPositionInRectangle(game.screenRect));
		}

		// Init rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			SetRockPosition(game.rocks[i], GetRandomPositionInRectangle(game.screenRect));
		}

		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0;
	}

	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

		game.screenRect = { 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT };

		InitPlayer(game.player, game);

		// Init apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			InitApple(game.apples[i], game);
		}

		// Init rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			InitRock(game.rocks[i], game);
		}

		game.background.setSize(sf::Vector2f(game.screenRect.size.x, game.screenRect.size.y));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		game.eatAppleSound.setBuffer(game.eatAppleSoundBuffer);
		game.gameOverSound.setBuffer(game.gameOverSoundBuffer);

		RestartGame(game);
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		// Update game state
		if (!game.isGameFinished)
		{
			// Handle input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				SetPlayerDirection(game.player, PlayerDirection::Right);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				SetPlayerDirection(game.player, PlayerDirection::Up);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				SetPlayerDirection(game.player, PlayerDirection::Left);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				SetPlayerDirection(game.player, PlayerDirection::Down);
			}

			UpdatePlayer(game.player, deltaTime);

			// Find player collisions with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				if (DoShapesCollide(GetPlayerCollider(game.player), GetAppleCollider(game.apples[i])))
				{
					SetApplePosition(game.apples[i], GetRandomPositionInRectangle(game.screenRect));
					++game.numEatenApples;
					SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
					game.eatAppleSound.play();
				}
			}

			// Find player collisions with rocks
			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				if (DoShapesCollide(GetPlayerCollider(game.player), GetRockCollider(game.rocks[i])))
				{
					game.isGameFinished = true;
					game.timeSinceGameFinish = 0.f;
					game.gameOverSound.play();
				}
			}

			// Check screen borders collision
			if (!DoShapesCollide(GetPlayerCollider(game.player), game.screenRect))
			{
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;
				game.gameOverSound.play();
			}
		}
		else
		{
			if (game.timeSinceGameFinish <= PAUSE_LENGTH)
			{
				game.timeSinceGameFinish += deltaTime;
				game.background.setFillColor(sf::Color::Red);
			}
			else
			{
				// Reset backgound
				game.background.setFillColor(sf::Color::Black);

				RestartGame(game);
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background);
		DrawPlayer(game.player, window);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			DrawApple(game.apples[i], window);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			DrawRock(game.rocks[i], window);
		}

	}

	void DeinializeGame(Game& game)
	{

	}
}
