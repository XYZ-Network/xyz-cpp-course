#include "GameStateRecords.h"
#include "Text.h"
#include "Game.h"
#include "GameSettings.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	void InitGameStateRecords(GameStateRecordsData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.titleText.setString("RECORDS");
		data.titleText.setFont(data.font);
		data.titleText.setFillColor(sf::Color::Red);
		data.titleText.setCharacterSize(48);

		data.tableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		std::map<int, std::string> sortedRecordsTable;
		for (const auto& item : game.recordsTable)
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) // Note, we can do several actions in for action block
		{
			data.tableTexts.emplace_back(); // Create text in place
			sf::Text& text = data.tableTexts.back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		data.hintText.setString("Press ESC to return back to main menu");
		data.hintText.setFont(data.font);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setCharacterSize(24);
	}

	void ShutdownGameStateRecords(GameStateRecordsData& data, Game& game)
	{
		// Nothing to clear here
	}

	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
		}
	}

	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.titleText.setOrigin(GetTextOrigin(data.titleText, { 0.5f, 0.f }));
		data.titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(data.titleText);

		// We need to create new vector here as DrawItemsList needs vector of pointers
		std::vector<sf::Text*> textsList;
		textsList.reserve(data.tableTexts.size());
		for (auto& text : data.tableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { data.titleText.getGlobalBounds().left, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });

		data.hintText.setOrigin(GetTextOrigin(data.hintText, { 0.5f, 1.f }));
		data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(data.hintText);
	}

}
