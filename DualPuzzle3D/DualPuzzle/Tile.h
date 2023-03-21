#pragma once
#include "Actor.h"

#include "SpriteComponent.h"


enum TileType {
	BACKGROUND,

	A_START,
	A_END,

	B_START,
	B_END,

	OBSTACLE,
	LIMIT
};

class Tile : public Actor
{
public:
	Tile(float widthP, float heightP);

	inline const TileType getType() { return type; }
	inline void setType(TileType typeP) { type = typeP; }

private:
	float width{ 0.0f };
	float height{ 0.0f };

	TileType type{ BACKGROUND };

	class SpriteComponent* spriteComponent;
	Texture texture;

	void setTexture();
};

