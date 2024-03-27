// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Game.h"

using namespace SnakeGame;

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEGHT), "SnakeGame");

	// We now use too much memory for stack, so we need to allocate it on heap
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	// Init game clock
	sf::Clock gameClock;
	
	// Game loop
	while (window.isOpen()) {
		
		float startTime = gameClock.getElapsedTime().asSeconds();
		
		HandleWindowEvents(*game, window);

		if (!window.isOpen()) {
			break;
		}

		if (UpdateGame(*game, TIME_PER_FRAME))
		{
			// Draw everything here
			// Clear the window first
			window.clear();

			DrawGame(*game, window);

			// End the current frame, display window contents on screen
			window.display();
		}
		else
		{
			window.close();
		}

		float endTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = endTime - startTime;
		if (deltaTime < TIME_PER_FRAME) {
			// Reduce framerate to not spam CPU and GPU
			sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime));
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;

	return 0;
}
