#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(data.font);
		startGame.text.setCharacterSize(24);
		startGame.onPressCallback = [](MenuItem&) {
			SwitchGameState(Application::Instance().GetGame(), GameStateType::Playing);
			};
		
		bool isInfiniteApples = IsEnableOptions(Application::Instance().GetGame(), GameOptions::InfiniteApples);
		MenuItem optionsInfiniteApplesItem;
		optionsInfiniteApplesItem.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));
		optionsInfiniteApplesItem.text.setFont(data.font);
		optionsInfiniteApplesItem.text.setCharacterSize(24);
		optionsInfiniteApplesItem.onPressCallback = [](MenuItem& item) {
			Game& game = Application::Instance().GetGame();
			game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::InfiniteApples);
			bool isInfiniteApples = IsEnableOptions(game, GameOptions::InfiniteApples);
			item.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));
			};

		bool isWithAcceleration = IsEnableOptions(Application::Instance().GetGame(), GameOptions::WithAcceleration);
		MenuItem optionsWithAccelerationItem;
		optionsWithAccelerationItem.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
		optionsWithAccelerationItem.text.setFont(data.font);
		optionsWithAccelerationItem.text.setCharacterSize(24);
		optionsWithAccelerationItem.onPressCallback = [](MenuItem& item) {
			Game& game = Application::Instance().GetGame();
			game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::WithAcceleration);
			bool isWithAcceleration = IsEnableOptions(game, GameOptions::WithAcceleration);
			item.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
			};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(data.font);
		options.text.setCharacterSize(24);
		options.hintText.setString("Options");
		options.hintText.setFont(data.font);
		options.hintText.setCharacterSize(48);
		options.hintText.setFillColor(sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;
		options.childrens.push_back(optionsInfiniteApplesItem);
		options.childrens.push_back(optionsWithAccelerationItem);
		
		MenuItem recordsItem;
		recordsItem.text.setString("Records");
		recordsItem.text.setFont(data.font);
		recordsItem.text.setCharacterSize(24);
		recordsItem.onPressCallback = [](MenuItem&) {
			PushGameState(Application::Instance().GetGame(), GameStateType::Records, true);
			};

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(data.font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {
			SwitchGameState(Application::Instance().GetGame(), GameStateType::None);
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(data.font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [&data](MenuItem&) {
			data.menu.GoBack();
			};

		MenuItem exitGameItem;
		exitGameItem.text.setString("Exit Game");
		exitGameItem.text.setFont(data.font);
		exitGameItem.text.setCharacterSize(24);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(data.font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenu;
		mainMenu.hintText.setString("Snake Game");
		mainMenu.hintText.setFont(data.font);
		mainMenu.hintText.setCharacterSize(48);
		mainMenu.hintText.setFillColor(sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(recordsItem);
		mainMenu.childrens.push_back(exitGameItem);
		

		data.menu.Init(mainMenu);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				data.menu.GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				data.menu.PressOnSelectedItem();
			}
			
			Orientation orientation = data.menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				data.menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
						orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				data.menu.SwitchToNextMenuItem();
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta)
	{

	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &data.menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		data.menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}

}
