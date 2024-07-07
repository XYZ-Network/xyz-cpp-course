#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameStateData.h"
#include "Platform.h"
#include "Ball.h"
#include "LevelLoader.h"
#include "BlockFactory.h"
#include "IObserver.h"
#include "Bonus.h"

#include <unordered_map>

namespace ArkanoidGame
{
	class Game;
	class Block;
	class BlockFactory;

	enum class BonusType
	{
		BiggerPlatform,
		SlowBall,

		Count
	};

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;

	private:
		void createBlocks();
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX,
			bool& needInverseDirY);

		// Resources
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer bonusSoundBuffer;

		// Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound gameOverSound;
		sf::Sound bonusSound;

		//Blocks creator
		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
		int breackableBlocksCount = 0;

		//Levels
		LevelLoader levelLoder;
		int currentLevel = 0;


		//Bonus
		std::map<BonusType, Bonus> bonuses;
	};
}
