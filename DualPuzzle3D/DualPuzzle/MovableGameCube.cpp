#include "MovableGameCube.h"
#include "InputComponent.h"
#include "TileGridInputComponent.h"


MovableGameCube::MovableGameCube(float widthP, float heightP, int typeP) :
	GameCube { widthP, heightP, typeP }
{
	TileGridInputComponent* tileGridInputComponent = new TileGridInputComponent{ this };
}
