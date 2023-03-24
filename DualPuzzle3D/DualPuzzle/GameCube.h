#pragma once
#include "Tile.h"


class GameCube : public Tile
{
public:
	GameCube() = delete;
	GameCube(float widthP, float heightP, int typeP = TileType::DEFAULT);
};