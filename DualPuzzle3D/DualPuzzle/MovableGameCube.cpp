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

void MovableGameCube::setPosition(Vector3 positionP)
{
	previousPosition = position;
	position = positionP;
	mustRecomputeWorldTransform = true;
}
