#include "GameStateGameOver.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	const char* PLAYER_NAME = "Player";

	void InitGameStateGameOver(GameStateGameOverData& data)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.timeSinceGameOver = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200; // a means Alfa, opacity
		data.background.setFillColor(backgroundColor);

		data.gameOverText.setFont(data.font);
		data.gameOverText.setCharacterSize(48);
		data.gameOverText.setStyle(sf::Text::Bold);
		data.gameOverText.setFillColor(sf::Color::Red);
		data.gameOverText.setString("GAME OVER");
		
		data.recordsTableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::multimap<int, std::string> sortedRecordsTable;
		Game& game = Application::Instance().GetGame();
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isSnakeInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) // Note, we can do several actions in for action block
		{
			data.recordsTableTexts.emplace_back(); // Create text in place
			sf::Text& text = data.recordsTableTexts.back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setCharacterSize(24);
			if (it->second == PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isSnakeInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		// If snake is not in table, replace last element with him
		if (!isSnakeInTable)
		{
			sf::Text& text = data.recordsTableTexts.back();
			std::stringstream sstream;
			int snakeScores = game.GetRecordByPlayerId(PLAYER_NAME);
			sstream << MAX_RECORDS_TABLE_SIZE << ". " << PLAYER_NAME << ": " << snakeScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

		data.hintText.setFont(data.font);
		data.hintText.setCharacterSize(24);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setString("Press Space to restart\nEsc to exit to main menu");
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, float timeDelta)
	{
		data.timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		data.gameOverText.setFillColor(gameOverTextColor);

	}

	void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.background.setOrigin(0.f, 0.f);
		data.background.setSize(viewSize);
		window.draw(data.background);

		data.gameOverText.setOrigin(GetTextOrigin(data.gameOverText, { 0.5f, 1.f }));
		data.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(data.gameOverText);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(data.recordsTableTexts.size());
		for (auto& text : data.recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		data.hintText.setOrigin(GetTextOrigin(data.hintText, { 0.5f, 1.f }));
		data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(data.hintText);
	}
}
