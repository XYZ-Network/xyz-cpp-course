#include "GameStatePauseMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

namespace ArkanoidGame
{
	void GameStatePauseMenuData::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		titleText.setString("Pause");
		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setFillColor(sf::Color::Red);

		MenuItem resumeItem;
		resumeItem.text.setString("Return to game");
		resumeItem.text.setFont(font);
		resumeItem.text.setCharacterSize(24);
		resumeItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().PopState();
			};

		MenuItem exitItem;
		exitItem.text.setString("Exit to main menu");
		exitItem.text.setFont(font);
		exitItem.text.setCharacterSize(24);
		exitItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().ExitGame();
			};

		MenuItem pauseMenu;
		pauseMenu.childrenOrientation = Orientation::Vertical;
		pauseMenu.childrenAlignment = Alignment::Middle;
		pauseMenu.childrens.push_back(resumeItem);
		pauseMenu.childrens.push_back(exitItem);

		menu.Init(pauseMenu);
	}

	void GameStatePauseMenuData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (event.key.code == sf::Keyboard::Up)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStatePauseMenuData::Update(float timeDelta)
	{

	}

	void GameStatePauseMenuData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		
		background.setSize(viewSize);
		window.draw(background);

		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.f }));
		titleText.setPosition(viewSize.x / 2.f, 100);
		window.draw(titleText);

		menu.Draw(window, window.getView().getCenter(), { 0.5f, 0.f });
	}

}
