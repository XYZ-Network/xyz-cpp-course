// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f; // Pixels per second
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f; // Pixels per second
const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;
const float PAUSE_LENGTH = 3.f;
const int NUM_ROCKS = 10;
const float ROCK_SIZE = 15.f;

struct Vector2D
{
	float x = 0;
	float y = 0;
};

enum class PlayerDirection
{
	Right = 0,
	Up,
	Left,
	Down
};

typedef Vector2D Position2D;

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Init player state
	Position2D playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = PlayerDirection::Right; 

	// Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerPosition.x, playerPosition.y);

	// Init apples
	Position2D applesPositions[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		applesPositions[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		applesPositions[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
		 
		applesShape[i].setRadius(APPLE_SIZE / 2.f);
		applesShape[i].setFillColor(sf::Color::Green);
		applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		applesShape[i].setPosition(applesPositions[i].x, applesPositions[i].y);
	}

	int numEatenApples = 0;

	// Init rocks
	Position2D rocksPositions[NUM_ROCKS];
	sf::RectangleShape rocksShape[NUM_ROCKS];
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		rocksPositions[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		rocksPositions[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;

		rocksShape[i].setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
		rocksShape[i].setFillColor(sf::Color::Yellow);
		rocksShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		rocksShape[i].setPosition(rocksPositions[i].x, rocksPositions[i].y);
	}

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	bool isGameFinished = false;
	float gameFinishTime = lastTime;
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	background.setFillColor(sf::Color::Black);
	background.setPosition(0.f, 0.f);

	// Main loop
	while (window.isOpen())
	{
		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
		}

		if (!isGameFinished)
		{
			// Handle input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerDirection = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerDirection = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerDirection = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerDirection = PlayerDirection::Down;
			}

			// Update player state
			switch (playerDirection)
			{
			case PlayerDirection::Right:
			{
				playerPosition.x += playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Up:
			{
				playerPosition.y -= playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Left:
			{
				playerPosition.x -= playerSpeed * deltaTime;
				break;
			}
			case PlayerDirection::Down:
			{
				playerPosition.y += playerSpeed * deltaTime;
				break;
			}
			}

			// Find player collisions with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				// Check collisions for squares
				/*
				float dx = fabs(playerPosition.x - applesPositions[i].x);
				float dy = fabs(playerPosition.y - applesPositions[i].y);
				if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
					dy <= (APPLE_SIZE + PLAYER_SIZE) / 2.f)
				{
					isAppleEaten[i] = true;
					++numEatenApples;
				}
				*/

				// Check collisions for circles
				float squareDistance = (playerPosition.x - applesPositions[i].x) * (playerPosition.x - applesPositions[i].x) +
					(playerPosition.y - applesPositions[i].y) * (playerPosition.y - applesPositions[i].y);
				float squareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;
				if (squareDistance <= squareRadiusSum)
				{
					applesPositions[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					applesPositions[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
					++numEatenApples;
					playerSpeed += ACCELERATION;
				}
			}

			// Find player collisions with rocks
			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				// Check collisions for squares
				
				float dx = fabs(playerPosition.x - rocksPositions[i].x);
				float dy = fabs(playerPosition.y - rocksPositions[i].y);
				if (dx <= (ROCK_SIZE + PLAYER_SIZE) / 2.f &&
					dy <= (ROCK_SIZE + PLAYER_SIZE) / 2.f)
				{
					isGameFinished = true;
					gameFinishTime = currentTime;
				}
			}

			// Check screen borders collision
			if (playerPosition.x - PLAYER_SIZE / 2.f < 0.f || playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				playerPosition.y - PLAYER_SIZE / 2.f < 0.f || playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				isGameFinished = true;
				gameFinishTime = currentTime;
			}
		}
		else
		{
			if (currentTime - gameFinishTime <= PAUSE_LENGTH)
			{
				background.setFillColor(sf::Color::Red);
			}
			else
			{
				// Reset backgound
				background.setFillColor(sf::Color::Black);
				
				// Reset player
				playerPosition.x = SCREEN_WIDTH / 2.f;
				playerPosition.y = SCREEN_HEIGHT / 2.f;
				playerSpeed = INITIAL_SPEED;
				playerDirection = PlayerDirection::Right;

				// Reset apples
				for (int i = 0; i < NUM_APPLES; ++i)
				{
					applesPositions[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					applesPositions[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
				}

				// Reset rocks
				for (int i = 0; i < NUM_ROCKS; ++i)
				{
					rocksPositions[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					rocksPositions[i].y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
				}

				// Reset game state
				numEatenApples = 0;
				isGameFinished = false;
			}
		}

		window.clear();
		window.draw(background);
		playerShape.setPosition(playerPosition.x, playerPosition.y);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			applesShape[i].setPosition(applesPositions[i].x, applesPositions[i].y);
			window.draw(applesShape[i]);
		}

		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			rocksShape[i].setPosition(rocksPositions[i].x, rocksPositions[i].y);
			window.draw(rocksShape[i]);
		}
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
