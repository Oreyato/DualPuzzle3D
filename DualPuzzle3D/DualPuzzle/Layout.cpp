#include "Layout.h"

#include "Consts.h"


int Layout::worldCoordinatesToIndex(Vector3 worldCoordinates)
{
	float xPos = worldCoordinates.x;
	float yPos = worldCoordinates.y;

	float xOffset = - Consts::Tile::WIDTH * colNb / 2.0f;
	float yOffset = - Consts::Tile::LENGTH * rowNb / 2.0f;

	int row = (xPos - xOffset) / Consts::Tile::WIDTH;
	int col = (yPos - yOffset) / Consts::Tile::LENGTH;

	int index = row + col * colNb;

	return index;
}
