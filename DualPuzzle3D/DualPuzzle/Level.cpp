#include "Level.h"

#include "Consts.h"


Level::Level(int columnsP, int rowsP) :
	columns{ columnsP },
	rows{ rowsP }
{
	tileWidth = Consts::Tile::WIDTH;
	tileLength = Consts::Tile::LENGTH;
}

Level::~Level()
{
}

void Level::generateLevel()
{
	float xOffset = tileWidth * rows / 2.0f;
	float yOffset = tileLength * columns / 2.0f;

	Vector2 offset{ xOffset, yOffset };

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++) {
			Tile* tile = new Tile(tileWidth, tileLength, TileType::A_END);
			Vector3 tilePosition{ row * tileWidth - offset.x, col * tileLength - offset.y, .0f };

			tile->setPosition(tilePosition);
			tile->setType(TileType::A_START);

			level.push_back(tile);
		}
	}

	std::cout << "Level size: " << level.size() << std::endl;
}
