#include "GameCube.h"

#include "Assets.h"
#include "MeshComponent.h"


GameCube::GameCube(float widthP, float heightP, int typeP) : Tile(widthP, heightP, typeP)
{
	meshComponent->setMesh(Assets::getMesh("GameCube_Tile"));

	setTexture();
}