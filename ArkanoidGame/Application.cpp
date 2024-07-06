#include "Application.h"
#include <cstdlib>

namespace ArkanoidGame
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	Application::Application() :
		window(sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT), SETTINGS.GAME_NAME)
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


			if (!window.isOpen()) {
				break;
			}
			game.UpdateGame(SETTINGS.TIME_PER_FRAME, window);


			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < SETTINGS.TIME_PER_FRAME) {
				// Reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(SETTINGS.TIME_PER_FRAME - deltaTime));
			}
		}
	}

}