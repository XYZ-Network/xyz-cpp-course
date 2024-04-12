#pragma once
#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Sprite.h"
#include "GameSettings.h"
#include <unordered_map>

namespace SnakeGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopState();

		// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);

		
	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;
	};

	void InitGameState(GameState& state);
	void ShutdownGameState(GameState& state);
	void HandleWindowEventGameState(GameState& state, sf::Event& event);
	void UpdateGameState(GameState& state, float timeDelta);
	void DrawGameState(GameState& state, sf::RenderWindow& window);
}
