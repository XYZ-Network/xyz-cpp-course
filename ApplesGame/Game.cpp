#include "Game.h"

void RestartGame(Game& game)
{
	InitPlayer(game.player);

	// Init apples
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(game.apples[i]);
	}

	// Init rocks
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		InitRock(game.rocks[i]);
	}

	game.numEatenApples = 0;
	game.isGameFinished = false;
	game.timeSinceGameFinish = 0;
}

void InitGame(Game& game)
{
	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.f, 0.f);

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
			game.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
		}

		// Update player state
		switch (game.player.direction)
		{
		case PlayerDirection::Right:
		{
			game.player.position.x += game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			game.player.position.y -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			game.player.position.x -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			game.player.position.y += game.player.speed * deltaTime;
			break;
		}
		}

		// Find player collisions with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				game.apples[i].position, APPLE_SIZE / 2.f))
			{
				game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				++game.numEatenApples;
				game.player.speed += ACCELERATION;
			}
		}

		// Find player collisions with rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
			{
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;
			}
		}

		// Check screen borders collision
		if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			game.isGameFinished = true;
			game.timeSinceGameFinish = 0.f;
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
	game.player.shape.setPosition(game.player.position.x, game.player.position.y);
	window.draw(game.player.shape);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		game.apples[i].shape.setPosition(game.apples[i].position.x, game.apples[i].position.y);
		window.draw(game.apples[i].shape);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		game.rocks[i].shape.setPosition(game.rocks[i].position.x, game.rocks[i].position.y);
		window.draw(game.rocks[i].shape);
	}

}

void DeinializeGame(Game& game)
{

}
