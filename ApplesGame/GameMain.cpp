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

Position2D GetRandomPositionInScreen()
{
	Position2D result;
	result.x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
	result.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
	return result;
}

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
	Position2D rect2Position, Vector2D rect2Size)
{
	float dx = fabs(rect1Position.x - rect2Position.x);
	float dy = fabs(rect1Position.y - rect2Position.y);
	return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
		dy <= (rect1Size.y + rect2Size.y) / 2.f);
}

bool IsCirclesCollide(Position2D circle1Position, float circle1Radius,
	Position2D circle2Position, float circle2Radius)
{
	float squareDistance = (circle1Position.x - circle2Position.x) * 
		(circle1Position.x - circle2Position.x) +
		(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
	float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
	return squareDistance <= squareRadiusSum;
}

struct GameState
{
	// Player data
	Position2D playerPosition;
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = PlayerDirection::Right;
	sf::RectangleShape playerShape;

	// Apples data
	Position2D applesPositions[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	// Rocks data
	Position2D rocksPositions[NUM_ROCKS];
	sf::RectangleShape rocksShape[NUM_ROCKS];

	// Global game data
	int numEatenApples = 0;
	bool isGameFinished = false;
	float timeSinceGameFinish = 0.f;
	sf::RectangleShape background;
};

void InitGame(GameState& gameState)
{
	// Init player state
	gameState.playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
	gameState.playerSpeed = INITIAL_SPEED;
	gameState.playerDirection = PlayerDirection::Right;

	// Init player shape
	gameState.playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	gameState.playerShape.setFillColor(sf::Color::Red);
	gameState.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);

	// Init apples
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		gameState.applesPositions[i] = GetRandomPositionInScreen();

		gameState.applesShape[i].setRadius(APPLE_SIZE / 2.f);
		gameState.applesShape[i].setFillColor(sf::Color::Green);
		gameState.applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		gameState.applesShape[i].setPosition(gameState.applesPositions[i].x, gameState.applesPositions[i].y);
	}

	// Init rocks
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		gameState.rocksPositions[i] = GetRandomPositionInScreen();

		gameState.rocksShape[i].setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
		gameState.rocksShape[i].setFillColor(sf::Color::Yellow);
		gameState.rocksShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		gameState.rocksShape[i].setPosition(gameState.rocksPositions[i].x, gameState.rocksPositions[i].y);
	}

	gameState.numEatenApples = 0;
	gameState.isGameFinished = false;
	gameState.timeSinceGameFinish = 0;
	
	gameState.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	gameState.background.setFillColor(sf::Color::Black);
	gameState.background.setPosition(0.f, 0.f);
}

void UpdateGame(GameState& gameState, float deltaTime)
{
	// Update game state
	if (!gameState.isGameFinished)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameState.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameState.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameState.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameState.playerDirection = PlayerDirection::Down;
		}

		// Update player state
		switch (gameState.playerDirection)
		{
		case PlayerDirection::Right:
		{
			gameState.playerPosition.x += gameState.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			gameState.playerPosition.y -= gameState.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			gameState.playerPosition.x -= gameState.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			gameState.playerPosition.y += gameState.playerSpeed * deltaTime;
			break;
		}
		}

		// Find player collisions with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsCirclesCollide(gameState.playerPosition, PLAYER_SIZE / 2.f,
				gameState.applesPositions[i], APPLE_SIZE / 2.f))
			{
				gameState.applesPositions[i] = GetRandomPositionInScreen();
				++gameState.numEatenApples;
				gameState.playerSpeed += ACCELERATION;
			}
		}

		// Find player collisions with rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (IsRectanglesCollide(gameState.playerPosition, { PLAYER_SIZE, PLAYER_SIZE },
				gameState.rocksPositions[i], {ROCK_SIZE, ROCK_SIZE}))
			{
				gameState.isGameFinished = true;
				gameState.timeSinceGameFinish = 0.f;
			}
		}

		// Check screen borders collision
		if (gameState.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || gameState.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			gameState.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || gameState.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			gameState.isGameFinished = true;
			gameState.timeSinceGameFinish = 0.f;
		}
	}
	else
	{
		if (gameState.timeSinceGameFinish <= PAUSE_LENGTH)
		{
			gameState.timeSinceGameFinish += deltaTime;
			gameState.background.setFillColor(sf::Color::Red);
		}
		else
		{
			// Reset backgound
			gameState.background.setFillColor(sf::Color::Black);

			// Reset player
			gameState.playerPosition.x = SCREEN_WIDTH / 2.f;
			gameState.playerPosition.y = SCREEN_HEIGHT / 2.f;
			gameState.playerSpeed = INITIAL_SPEED;
			gameState.playerDirection = PlayerDirection::Right;

			// Reset apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				gameState.applesPositions[i] = GetRandomPositionInScreen();
			}

			// Reset rocks
			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				gameState.rocksPositions[i] = GetRandomPositionInScreen();
			}

			// Reset game state
			gameState.numEatenApples = 0;
			gameState.isGameFinished = false;
			gameState.timeSinceGameFinish = 0.f;
		}
	}
}

void DrawGame(GameState& gameState, sf::RenderWindow& window)
{
	window.draw(gameState.background);
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);
	window.draw(gameState.playerShape);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		gameState.applesShape[i].setPosition(gameState.applesPositions[i].x, gameState.applesPositions[i].y);
		window.draw(gameState.applesShape[i]);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		gameState.rocksShape[i].setPosition(gameState.rocksPositions[i].x, gameState.rocksPositions[i].y);
		window.draw(gameState.rocksShape[i]);
	}

}

void DeinializeGame(GameState& gameState)
{

}

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	GameState gameState;
	InitGame(gameState);
	
	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

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

		UpdateGame(gameState, deltaTime);

		// Draw game
		window.clear();
		DrawGame(gameState, window);

		window.display();
	}

	// Deinitialization
	DeinializeGame(gameState);

	return 0;
}
