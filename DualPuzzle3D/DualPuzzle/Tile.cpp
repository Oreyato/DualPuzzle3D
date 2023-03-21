#include "Tile.h"

#include "Assets.h"


Tile::Tile(float widthP, float heightP) :
	width{ widthP },
	height{ heightP }
{
	texture = Assets::getTexture("Default");

	spriteComponent = new SpriteComponent(this, texture);

	setTexture();
}

void Tile::setTexture()
{
	std::string textureName{ "" };

	switch (type)
	{
	case BACKGROUND:
		textureName = "Background";
		break;
	case A_START:
		textureName = "A_Start";
		break;
	case A_END:
		textureName = "A_End";
		break;
	case B_START:
		textureName = "B_Start";
		break;
	case B_END:
		textureName = "B_End";
		break;
	case OBSTACLE:
		textureName = "Obstacle";
		break;
	case LIMIT:
		textureName = "Limit";
		break;
	default:
		textureName = "Default";
		break;
	}

	spriteComponent->setTexture(Assets::getTexture(textureName));
}
