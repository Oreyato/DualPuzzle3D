#include "MovableGameCube.h"
#include "InputComponent.h"


MovableGameCube::MovableGameCube(float widthP, float heightP, int typeP) :
	GameCube { widthP, heightP, typeP }
{
	InputComponent* inputComponent = new InputComponent{ this };
}
