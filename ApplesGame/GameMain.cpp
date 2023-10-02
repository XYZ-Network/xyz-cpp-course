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

struct Player
{
	Position2D position;
	float speed = INITIAL_SPEED;
	PlayerDirection direction = PlayerDirection::Right;
	sf::RectangleShape shape;
};

void InitPlayer(Player& player)
{
	// Init player state
	player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Right;

	// Init player shape
	player.shape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.shape.setFillColor(sf::Color::Red);
	player.shape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	player.shape.setPosition(player.position.x, player.position.y);
}

struct Apple
{
	Position2D position;
	sf::CircleShape shape;
};

void InitApple(Apple& apple)
{
	apple.position = GetRandomPositionInScreen();
	
	apple.shape.setRadius(APPLE_SIZE / 2.f);
	apple.shape.setFillColor(sf::Color::Green);
	apple.shape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	apple.shape.setPosition(apple.position.x, apple.position.y);
}

struct Rock
{
	Position2D position;
	sf::RectangleShape shape;
};


void InitRock(Rock& rock)
{
	rock.position = GetRandomPositionInScreen();

	rock.shape.setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
	rock.shape.setFillColor(sf::Color::White);
	rock.shape.setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);
	rock.shape.setPosition(rock.position.x, rock.position.y);
}

struct GameState
{
	Player player;
	Apple apples[NUM_APPLES];
	Rock rocks[NUM_ROCKS];

	// Global game data
	int numEatenApples = 0;
	bool isGameFinished = false;
	float timeSinceGameFinish = 0.f;
	sf::RectangleShape background;
};

void RestartGame(GameState& gameState)
{
	InitPlayer(gameState.player);

	// Init apples
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(gameState.apples[i]);
	}

	// Init rocks
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		InitRock(gameState.rocks[i]);
	}

	gameState.numEatenApples = 0;
	gameState.isGameFinished = false;
	gameState.timeSinceGameFinish = 0;
}

void InitGame(GameState& gameState)
{	
	gameState.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	gameState.background.setFillColor(sf::Color::Black);
	gameState.background.setPosition(0.f, 0.f);

	RestartGame(gameState);
}

void UpdateGame(GameState& gameState, float deltaTime)
{
	// Update game state
	if (!gameState.isGameFinished)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameState.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameState.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameState.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameState.player.direction = PlayerDirection::Down;
		}

		// Update player state
		switch (gameState.player.direction)
		{
		case PlayerDirection::Right:
		{
			gameState.player.position.x += gameState.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			gameState.player.position.y -= gameState.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			gameState.player.position.x -= gameState.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			gameState.player.position.y += gameState.player.speed * deltaTime;
			break;
		}
		}

		// Find player collisions with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsCirclesCollide(gameState.player.position, PLAYER_SIZE / 2.f,
				gameState.apples[i].position, APPLE_SIZE / 2.f))
			{
				gameState.apples[i].position = GetRandomPositionInScreen();
				++gameState.numEatenApples;
				gameState.player.speed += ACCELERATION;
			}
		}

		// Find player collisions with rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (IsRectanglesCollide(gameState.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				gameState.rocks[i].position, {ROCK_SIZE, ROCK_SIZE}))
			{
				gameState.isGameFinished = true;
				gameState.timeSinceGameFinish = 0.f;
			}
		}

		// Check screen borders collision
		if (gameState.player.position.x - PLAYER_SIZE / 2.f < 0.f || gameState.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			gameState.player.position.y - PLAYER_SIZE / 2.f < 0.f || gameState.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
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

			RestartGame(gameState);
		}
	}
}

void DrawGame(GameState& gameState, sf::RenderWindow& window)
{
	window.draw(gameState.background);
	gameState.player.shape.setPosition(gameState.player.position.x, gameState.player.position.y);
	window.draw(gameState.player.shape);
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		gameState.apples[i].shape.setPosition(gameState.apples[i].position.x, gameState.apples[i].position.y);
		window.draw(gameState.apples[i].shape);
	}

	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		gameState.rocks[i].shape.setPosition(gameState.rocks[i].position.x, gameState.rocks[i].position.y);
		window.draw(gameState.rocks[i].shape);
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
