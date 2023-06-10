#pragma once

#include "Component.h"

#include <SDL_stdinc.h>
#include <SDL_scancode.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Layout.h"


class TileGridInputComponent :
	public Component
{
public:
	TileGridInputComponent(Actor* ownerP);
	TileGridInputComponent() = delete;
	TileGridInputComponent(const TileGridInputComponent&) = delete;
	TileGridInputComponent& operator=(const TileGridInputComponent&) = delete;

	void processInput(const struct InputState& inputState);

	void update(float dt) override;

	void setLevelLayout(Layout layoutP);

private:
	bool needUpdate;

	float movementUnit;
	Vector2 direction;

	SDL_Scancode topKey;
	SDL_Scancode downKey;
	SDL_Scancode leftKey;
	SDL_Scancode rightKey;

	Layout levelLayout;

	bool canMoveTo(Vector3 targetPositionP);
};

