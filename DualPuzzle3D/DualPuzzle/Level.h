#pragma once

#include <vector>

#include "Tile.h"
#include "Layout.h"


class Level
{
public:
	Level(int levelIndexP = 0);
	~Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;

	void generateLevel();
	inline std::vector<Tile*> getLevel() { return level; }

	inline int getCurrentLevelIndex() { return currentLevelIndex; }
	void setLevel(int levelIndex);

private:
	float tileWidth{ 1.0f };
	float tileLength{ 1.0f };

	int currentLevelIndex{ 0 };

	std::vector<Tile*> level;

	std::vector<Layout> levelLayouts;
	void fillLayouts();
};

