#include "MovableGameCube.h"


MovableGameCube::MovableGameCube(float widthP, float heightP, int typeP) :
	GameCube { widthP, heightP, typeP }
{
	tileGridInputComponent = new TileGridInputComponent{ this };
}

TileGridInputComponent* MovableGameCube::getTileGridInputComponent()
{
	return tileGridInputComponent;
}
