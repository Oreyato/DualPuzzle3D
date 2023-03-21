#pragma once
#include "Actor.h"

#include "SpriteComponent.h"


class Tile : public Actor
{
public:
	Tile(float widthP, float heightP);
	
private:
	float width{ 0.0f };
	float height{ 0.0f };

	class SpriteComponent* spriteComponent;
	Texture texture;
};

