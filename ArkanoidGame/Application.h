#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ArkanoidGame {
	
	class Application
	{
	public:
		Application(const Application& app) = delete;
		Application& operator= (const Application&) = delete;
		
		static Application& Instance();

		void Run();

		Game& GetGame() { return game; }

	private:
		Application();
		~Application() = default;

	private:
		Game game;
		sf::RenderWindow window;
	};

}


