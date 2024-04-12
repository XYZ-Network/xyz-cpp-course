#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace SnakeGame
{
	Game::Game()
	{
		// Generate fake records table
		recordsTable =
		{
			{"John", MAX_APPLES / 2},
			{"Jane", MAX_APPLES / 3 },
			{"Alice", MAX_APPLES / 4 },
			{"Bob", MAX_APPLES / 5 },
			{"Clementine", MAX_APPLES / 5 },
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				HandleWindowEventGameState(stateStack.back(), event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack.size() > 0)
			{
				ShutdownGameState(stateStack.back());
				stateStack.pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack.size() > 0)
			{
				ShutdownGameState(stateStack.back());
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			stateStack.push_back({ pendingGameStateType, nullptr, pendingGameStateIsExclusivelyVisible });
			InitGameState(stateStack.back());
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			UpdateGameState(stateStack.back(), timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(**it, window);
			}
		}
	}

	void Game::Shutdown()
	{
		// Shutdown all game states
		while (stateStack.size() > 0)
		{
			ShutdownGameState(stateStack.back());
			stateStack.pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}

	void InitGameState(GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data);
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data = new GameStatePauseMenuData();
			InitGameStatePauseMenu(*(GameStatePauseMenuData*)state.data);
			break;
		}
		case GameStateType::Records:
		{
			state.data = new GameStateRecordsData();
			InitGameStateRecords(*(GameStateRecordsData*)state.data);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void ShutdownGameState(GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data);
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			ShutdownGameStatePlaying(*(GameStatePlayingData*)state.data);
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data);
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			ShutdownGameStatePauseMenu(*(GameStatePauseMenuData*)state.data);
			delete (GameStatePauseMenuData*)state.data;
			break;
		}
		case GameStateType::Records:
		{
			ShutdownGameStateRecords(*(GameStateRecordsData*)state.data);
			delete (GameStateRecordsData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}

		state.data = nullptr;
	}

	void HandleWindowEventGameState(GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			HandleGameStatePauseMenuWindowEvent(*(GameStatePauseMenuData*)state.data, event);
			break;
		}
		case GameStateType::Records:
		{
			HandleGameStateRecordsWindowEvent(*(GameStateRecordsData*)state.data, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void UpdateGameState(GameState& state, float timeDelta)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			UpdateGameStatePauseMenu(*(GameStatePauseMenuData*)state.data, timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			UpdateGameStateRecords(*(GameStateRecordsData*)state.data, timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void DrawGameState(GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			DrawGameStatePauseMenu(*(GameStatePauseMenuData*)state.data, window);
			break;
		}
		case GameStateType::Records:
		{
			DrawGameStateRecords(*(GameStateRecordsData*)state.data, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
}
