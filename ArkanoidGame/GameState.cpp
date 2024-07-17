#include "GameState.h"
#include "GameStateData.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateGameWin.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

#include <assert.h>


namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = std::make_shared<GameStateMainMenuData>();
			break;
		}
		case GameStateType::Playing:
		{
			data = std::make_shared<GameStatePlayingData>();
			break;
		}
		case GameStateType::GameOver:
		{
			data = std::make_shared<GameStateGameOverData>();
			break;
		}
		case GameStateType::GameWin:
		{
			data = std::make_shared<GameStateGameWinData>();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = std::make_shared<GameStatePauseMenuData>();
			break;
		}
		case GameStateType::Records:
		{
			data = std::make_shared<GameStateRecordsData>();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
		if (data) {
			data->Init();
		}
	}

	GameState::~GameState()
	{
		if (data) {
			data = nullptr;
		}
	}

	void GameState::Update(float timeDelta)
	{
		data->Update(timeDelta);
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		data->Draw(window);
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		data->HandleWindowEvent(event);
	}
}