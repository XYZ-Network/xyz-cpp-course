#include "Application.h"
#include <cstdlib>

namespace SnakeGame
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	Application::Application() :
		window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEGHT), GAME_NAME)
	{
		// Init random number generator
		unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
		srand(seed);
	}

	void Application::Run()
	{
		// Init game clock
		sf::Clock gameClock;

		// Game loop
		while (window.isOpen()) {

			float startTime = gameClock.getElapsedTime().asSeconds();

			game.HandleWindowEvents(window);

			if (!window.isOpen()) {
				break;
			}

			if (game.Update(TIME_PER_FRAME))
			{
				// Draw everything here
				// Clear the window first
				window.clear();

				game.Draw(window);

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
	}

}