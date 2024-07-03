#include "GameStatePlaying.h"
#include "Application.h"
#include "Block.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f })));
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f } )));
		for (int row = 0; row < BLOCKS_COUNT_ROWS; ++row) {
			for (int col = 0; col < BLOCKS_COUNT_IN_ROW; ++col) {
				gameObjects.emplace_back(std::make_shared<Block>(sf::Vector2f({ BLOCK_SHIFT + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + row * BLOCK_HEIGHT })));
			}
		}

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		for (auto&& object : gameObjects) {
			object->Update(timeDelta);
		}

		const Platform* platform = (Platform*)gameObjects[0].get();
		Ball* ball = (Ball*)gameObjects[1].get();

		const bool isCollision = platform->CheckCollisionWithBall(*ball);
		if (isCollision) {
			ball->InvertDirectionY();
		}

		bool needInverseDirX = false;
		bool needInverseDirY = false;
		for (size_t i = 2; i < gameObjects.size(); ++i) {
			const auto block = (Block*)gameObjects[i].get();
			if (block->CheckCollisionWithBall(*ball)) {
				const auto ballPos = ball->GetPosition();
				const auto blockRect = block->GetRect();

				if (ballPos.y > blockRect.top + blockRect.height && ballPos.x >= blockRect.left && ballPos.x <= blockRect.left + blockRect.width) {
					needInverseDirY = true;
				}

				if (ballPos.y < blockRect.top && ballPos.x >= blockRect.left && ballPos.x <= blockRect.left + blockRect.width) {
					needInverseDirY = true;
				}

				if (ballPos.x < blockRect.left && ballPos.y >= blockRect.top && ballPos.y <= blockRect.top + blockRect.height) {
					needInverseDirX = true;
				}

				if (ballPos.x > blockRect.left + blockRect.width && ballPos.y >= blockRect.top && ballPos.y <= blockRect.top + blockRect.height) {
					needInverseDirX = true;
				}

				std::swap(gameObjects[i], gameObjects.back());
				gameObjects.pop_back();
				i--;
			}
		}
		if (needInverseDirX) {
			ball->InvertDirectionX();
		}
		if (needInverseDirY) {
			ball->InvertDirectionY();
		}

		const bool isGameWin = gameObjects.size() == 2;
		const bool isGameOver = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		Game& game = Application::Instance().GetGame();

		if (isGameWin) {
			game.PushState(GameStateType::GameWin, false);
		} else if (isGameOver) {
			gameOverSound.play();
			
			game.PushState(GameStateType::GameOver, false);
		}

	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game objects
		for (auto&& object : gameObjects) {
			object->Draw(window);
		}


		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
