#pragma once
#include <string>


namespace ArkanoidGame
{
	class GameWorld {
	private:

		GameWorld() = default;
	public:
		static GameWorld& Instance() {
			static GameWorld gameWorld;
			return gameWorld;
		}


		// Resources path
		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";

		// Game settings constants
		const float ACCELERATION = 10.f;
		const int MAX_APPLES = 80;
		const unsigned int SCREEN_WIDTH = 800;
		const unsigned int SCREEN_HEIGHT = 600;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		const unsigned int BALL_SIZE = 20;
		const unsigned int BALL_SPEED = 400;

		const unsigned int PLATFORM_WIDTH = 60;
		const unsigned int PLATFORM_HEIGHT = 20;
		const float PLATFORM_SPEED = 300.f;

		const unsigned int BLOCKS_COUNT_ROWS = 4;
		const unsigned int BLOCKS_COUNT_IN_ROW = 15;
		const unsigned int BLOCK_SHIFT = 5;
		const unsigned int BLOCK_WIDTH = (SCREEN_WIDTH - (BLOCKS_COUNT_IN_ROW + 1) * BLOCK_SHIFT) / BLOCKS_COUNT_IN_ROW;
		const unsigned int BLOCK_HEIGHT = 20;

		const int MAX_RECORDS_TABLE_SIZE = 5;
		const char* PLAYER_NAME = "Player";

		const std::string GAME_NAME = "ArkanoidGame";
		const float BREAK_DELAY = 1.f;
		const float BONUS_DURATION = 30.f;
		const int BONUS_PROPABILITY_PERCENT = 5;
	};
}

#define SETTINGS GameWorld::Instance()