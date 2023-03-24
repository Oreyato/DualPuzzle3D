#include "Tile.h"

#include "Assets.h"


Tile::Tile(float widthP, float heightP, int typeP) :
	width{ widthP },
	height{ heightP },
	type{ typeP }
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_Tile"));

	setTexture();
}

void Tile::setTexture()
{
	meshComponent->setTextureIndex(type);
}
