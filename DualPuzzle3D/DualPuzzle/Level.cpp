#include "Level.h"

#include "Consts.h"
#include "Cube.h"


Level::Level(int levelIndexP) :
	currentLevelIndex{ levelIndexP }
{
	tileWidth = Consts::Tile::WIDTH;
	tileLength = Consts::Tile::LENGTH;

	fillLayouts();
	generateLevel();
}

Level::~Level()
{
}

void Level::generateLevel()
{
	Layout* currentLayout = &levelLayouts[currentLevelIndex];

	int rows = currentLayout->rowNb;
	int columns = currentLayout->colNb;

	float xOffset = tileWidth * rows / 2.0f;
	float yOffset = tileLength * columns / 2.0f;

	Vector2 offset{ xOffset, yOffset };

	int index{ 0 };

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++) {
			int desc = currentLayout->description[index];

			Tile* tile = new Tile(tileWidth, tileLength, desc);
			Vector3 pos{ col * tileLength - offset.y, row * tileWidth - offset.x, .0f };

			tile->setPosition(pos);
			tile->setType(TileType::A_START);

			if (desc != TileType::BACKGROUND && desc != TileType::LIMIT) {
				Cube* testCube = new Cube();
				testCube->setPosition(Vector3{ pos });
				testCube->setScale(100.0f);
			}

			level.push_back(tile);

			index++;
		}
	}

	std::cout << "Level size: " << level.size() << std::endl;
}

void Level::setLevel(int levelIndex)
{
	currentLevelIndex = levelIndex;

	generateLevel();
}

void Level::fillLayouts()
{
	levelLayouts.emplace_back(Layout{
		0,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
		});
	levelLayouts.emplace_back(Layout{
		1,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	6,	6,	6,	6,	1,	1,	1,	1,	6,	4,	1,	1,	7,
			7,	2,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	6,	1,	1,	5,	6,	6,	6,	6,	7,
			7,	6,	6,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	3,	1,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		2,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	4,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	6,	6,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	6,	1,	1,	6,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	6,	1,	5,	1,	1,	7,
			7,	1,	6,	6,	1,	1,	1,	1,	6,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	6,	3,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		3,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	6,	6,	3,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	6,	1,	1,	1,	1,	1,	1,	6,	6,	1,	7,
			7,	1,	6,	1,	1,	1,	1,	1,	1,	1,	4,	1,	1,	7,
			7,	1,	6,	1,	5,	1,	6,	6,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		4,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	1,	5,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	1,	1,	1,	1,	6,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	3,	1,	6,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	4,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	6,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		4,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	3,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	6,	6,	1,	1,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	6,	6,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	6,	1,	1,	6,	6,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	4,	1,	5,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
}