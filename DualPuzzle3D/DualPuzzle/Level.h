#pragma once

#include <vector>

#include "Tile.h"


class Level
{
public:
	Level(int widthP, int heightP);
	~Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;

	void generateLevel();
	inline std::vector<Tile*> getLevel() { return level; }

private:
	int columns{ 1 };
	int rows{ 1 };

	float tileWidth{ 1.0f };
	float tileLength{ 1.0f };

	std::vector<Tile*> level;
};

