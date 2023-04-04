#include "Tile.h"

#include "Assets.h"


Tile::Tile(float widthP, float heightP, int typeP) :
	width{ widthP },
	height{ heightP },
	type{ typeP }
{
	//meshComponent = new MeshComponent(this);
	//meshComponent->setMesh(Assets::getMesh("Mesh_Tile"));

	animMeshComponent = new AnimMeshComponent(this);
	animMeshComponent->setMesh(Assets::getMesh("Mesh_Tile"));
	animMeshComponent->setAnimFPS(10.0f);

	setTexture();
}

void Tile::setTexture()
{
	//meshComponent->setTextureIndex(type);
	animMeshComponent->setTextureIndex(type);

	std::vector<Texture*> animTextures;

	if (type == TileType::LIMIT) {
		animTextures.push_back(&Assets::getTexture("Limit_0"));
		animTextures.push_back(&Assets::getTexture("Limit_1"));
		animTextures.push_back(&Assets::getTexture("Limit_2"));
	}
	else if (type == TileType::A_START) {
		animTextures.push_back(&Assets::getTexture("A_Start_0"));
		animTextures.push_back(&Assets::getTexture("A_Start_1"));
		animTextures.push_back(&Assets::getTexture("A_Start_2"));
	}

	animMeshComponent->setAnimTextures(animTextures);
}
