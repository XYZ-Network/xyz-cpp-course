#include "GameStateGameWin.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStateGameWinData::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameWin = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200; // a means Alfa, opacity
		background.setFillColor(backgroundColor);

		gameWinText.setFont(font);
		gameWinText.setCharacterSize(48);
		gameWinText.setStyle(sf::Text::Bold);
		gameWinText.setFillColor(sf::Color::Green);
		gameWinText.setString("GAME WIN");

		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Press Space to restart\nEsc to exit to main menu");
	}

	void GameStateGameWinData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				Application::Instance().GetGame().StartGame();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStateGameWinData::Update(float timeDelta)
	{
		timeSinceGameWin += timeDelta;

		sf::Color GameWinTextColor = (int)timeSinceGameWin % 2 ? sf::Color::Green : sf::Color::Yellow;
		gameWinText.setFillColor(GameWinTextColor);
	}

	void GameStateGameWinData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);

		gameWinText.setOrigin(GetTextOrigin(gameWinText, { 0.5f, 1.f }));
		gameWinText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(gameWinText);

		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 1.f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(hintText);
	}
}
