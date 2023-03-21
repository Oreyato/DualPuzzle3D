#include "Tile.h"

#include "Assets.h"


Tile::Tile(float widthP, float heightP) :
	width{ widthP },
	height{ heightP }
{
	texture = Assets::getTexture("BackgroundTest");

	spriteComponent = new SpriteComponent(this, texture);
}
