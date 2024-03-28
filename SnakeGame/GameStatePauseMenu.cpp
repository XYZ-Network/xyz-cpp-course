#include "GameStatePauseMenu.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStatePauseMenu(GameStatePauseMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		data.titleText.setString("Pause");
		data.titleText.setFont(data.font);
		data.titleText.setCharacterSize(48);
		data.titleText.setFillColor(sf::Color::Red);

		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.children.push_back(&data.resumeItem);
		data.menu.rootItem.children.push_back(&data.exitItem);
		
		data.resumeItem.text.setString("Return to game");
		data.resumeItem.text.setFont(data.font);
		data.resumeItem.text.setCharacterSize(24);

		data.exitItem.text.setString("Exit to main menu");
		data.exitItem.text.setFont(data.font);
		data.exitItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.resumeItem);
	}

	void ShutdownGameStatePauseMenu(GameStatePauseMenuData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePauseMenuWindowEvent(GameStatePauseMenuData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}

			if (data.menu.selectedItem == nullptr)
			{
				return;
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.resumeItem)
				{
					PopGameState(game);
				}
				else if (data.menu.selectedItem == &data.exitItem)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (event.key.code == sf::Keyboard::Up)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStatePauseMenu(GameStatePauseMenuData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStatePauseMenu(GameStatePauseMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		
		data.background.setSize(viewSize);
		window.draw(data.background);

		data.titleText.setOrigin(GetTextOrigin(data.titleText, { 0.5f, 0.f }));
		data.titleText.setPosition(viewSize.x / 2.f, 100);
		window.draw(data.titleText);

		DrawMenu(data.menu, window, window.getView().getCenter(), { 0.5f, 0.f });
	}

}
