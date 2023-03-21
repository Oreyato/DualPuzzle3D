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
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++) {
			Tile* tile = new Tile(tileWidth, tileLength);
			Vector3 tilePosition{ row * tileWidth, col * tileLength, 0.0f };

			tile->setPosition(tilePosition);

			level.push_back(tile);
		}
	}

	std::cout << "Level size: " << level.size() << std::endl;
}
