#pragma once

#include <vector>

#include "Tile.h"
#include "Layout.h"
#include "MovableGameCube.h"

class Game;

class Level
{
public:
	Level(int levelIndexP = 0);
	~Level();

	Level(const Level&) = delete;

	void generateLevel();
	
	void update(float dt);

	inline Game& getGame() { return game; }
	inline std::vector<Tile*> getLevel() { return level; }
	inline int getCurrentLevelIndex() { return currentLevelIndex; }
	
	void setLevel(int levelIndex);

	void clean();

private:
	Game& game;

	float tileWidth{ 1.0f };
	float tileLength{ 1.0f };

	int currentLevelIndex{ 0 };

	std::vector<Tile*> level;
	std::vector<Actor*> actors;
	std::vector<MovableGameCube*> playerCharacters;

	std::vector<Layout> levelLayouts;
	Layout currentLayout;
	void fillLayouts();
};

