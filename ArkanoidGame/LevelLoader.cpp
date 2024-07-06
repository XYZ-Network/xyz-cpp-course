#include "LevelLoader.h"
#include "GameSettings.h"

#include <fstream>
#include <assert.h>
#include <filesystem>

namespace ArkanoidGame {
	Level& LevelLoader::GetLevel(int i) {
		return levels.at(i);
	}

	BlockType LevelLoader::CharToBlockType(char symbol) {
		BlockType blockType;
		switch (symbol)
		{
		case '1':
			blockType = BlockType::Simple;
			break;
		case '2':
			blockType = BlockType::ThreeHit;
			break;
		case '0':
			blockType = BlockType::Unbreackable;
			break;
		default:
			assert(false);
			break;
		}
		return blockType;
	}

	void LevelLoader::LoadLevelsFromFile() {
		std::string filepath = SETTINGS.LEVELS_CONFIG_PATH;
		std::string line;
		std::ifstream file(filepath);
		int y = 0;
		while (getline(file, line)) {
			if (line.rfind("level ", 0) == 0) {
				auto level = std::stoi(line.substr(6, line.size() - 6));
				levels.emplace_back(Level());
				y = 0;
			}
			else
			{
				int x = 0;
				for (char c : line) {
					if (c != ' ') {
						levels.back().m_blocks.emplace_back(std::make_pair(sf::Vector2i{ x, y }, CharToBlockType(c)));
					}
					++x;
				}
			}
			++y;
		}
		file.close();
	}

	int LevelLoader::GetLevelCount()
	{
		return levels.size();
	}
}