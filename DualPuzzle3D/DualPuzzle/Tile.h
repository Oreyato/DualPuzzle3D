#pragma once
#include "Actor.h"

#include "MeshComponent.h"
#include "AnimMeshComponent.h"


enum TileType {
	DEFAULT,

	BACKGROUND,

	A_START,
	A_END,

	B_START,
	B_END,

	OBSTACLE,
	LIMIT,
	START
};

class Tile : public Actor
{
public:
	Tile(float widthP, float heightP, int typeP = TileType::DEFAULT);

	inline const int getType() { return type; }
	void setType(TileType typeP);
	void setType(int typeP);

	void setAnimatedTexture();

protected:
	float width{ 0.0f };
	float height{ 0.0f };

	int type;

	void setTexture();

	class MeshComponent* meshComponent;
	class AnimMeshComponent* animMeshComponent;
};

