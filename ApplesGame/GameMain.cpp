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

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Init player state
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - Down

	// Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	// Init apples
	float applesX[NUM_APPLES];
	float applesY[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	for (int i = 0; i < NUM_APPLES; ++i)
	{
		applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		applesY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
		 
		applesShape[i].setRadius(APPLE_SIZE / 2.f);
		applesShape[i].setFillColor(sf::Color::Green);
		applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		applesShape[i].setPosition(applesX[i], applesY[i]);
	}

	int numEatenApples = 0;

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
				playerDirection = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerDirection = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerDirection = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerDirection = 3;
			}

			// Update player state

			if (playerDirection == 0)
			{
				playerX += playerSpeed * deltaTime;
			}
			else if (playerDirection == 1)
			{
				playerY -= playerSpeed * deltaTime;
			}
			else if (playerDirection == 2)
			{
				playerX -= playerSpeed * deltaTime;
			}
			else if (playerDirection == 3)
			{
				playerY += playerSpeed * deltaTime;
			}

			// Find player collisions with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				// Check collisions for squares
				/*
				float dx = fabs(playerX - applesX[i]);
				float dy = fabs(playerY - applesY[i]);
				if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
					dy <= (APPLE_SIZE + PLAYER_SIZE) / 2.f)
				{
					isAppleEaten[i] = true;
					++numEatenApples;
				}
				*/

				// Check collisions for circles
				float squareDistance = (playerX - applesX[i]) * (playerX - applesX[i]) +
					(playerY - applesY[i]) * (playerY - applesY[i]);
				float squareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;
				if (squareDistance <= squareRadiusSum)
				{
					applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					applesY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
					++numEatenApples;
					playerSpeed += ACCELERATION;
				}
			}

			// Check screen borders collision
			if (playerX - PLAYER_SIZE / 2.f < 0.f || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				playerY - PLAYER_SIZE / 2.f < 0.f || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
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
				playerX = SCREEN_WIDTH / 2.f;
				playerY = SCREEN_HEIGHT / 2.f;
				playerSpeed = INITIAL_SPEED;
				playerDirection = 0;

				// Reset apples
				for (int i = 0; i < NUM_APPLES; ++i)
				{
					applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					applesY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
				}

				// Reset game state
				numEatenApples = 0;
				isGameFinished = false;
			}
		}

		window.clear();
		window.draw(background);
		playerShape.setPosition(playerX, playerY);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			applesShape[i].setPosition(applesX[i], applesY[i]);
			window.draw(applesShape[i]);
		}
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
