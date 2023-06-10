#include "TileGridInputComponent.h"

#include "InputSystem.h"
#include "Actor.h"
#include "Consts.h"
#include "Tile.h"


TileGridInputComponent::TileGridInputComponent(Actor* ownerP) :
	Component{ ownerP, 10 },

	needUpdate{ false },

	levelLayout{},

	movementUnit{ Consts::Tile::LENGTH },
	direction{ Vector2::zero },

	topKey{ SDL_SCANCODE_W },
	downKey{ SDL_SCANCODE_S },
	leftKey{ SDL_SCANCODE_A },
	rightKey{ SDL_SCANCODE_D }
{
}

void TileGridInputComponent::processInput(const InputState& inputState)
{
	float forwardSpeed{ 0.0f };

	if (inputState.keyboard.getKeyState(topKey) == ButtonState::Pressed) {
		direction.y = -1;
		needUpdate = true;
	}
	if (inputState.keyboard.getKeyState(downKey) == ButtonState::Pressed) {
		direction.y = 1;
		needUpdate = true;
	}
	if (inputState.keyboard.getKeyState(leftKey) == ButtonState::Pressed) {
		direction.x = -1;
		needUpdate = true;
	}
	if (inputState.keyboard.getKeyState(rightKey) == ButtonState::Pressed) {
		direction.x = 1;
		needUpdate = true;
	}
}

void TileGridInputComponent::update(float dt)
{
	if (needUpdate)
	{
		Vector3 newPosition = owner.getPosition();
		newPosition += Vector3{ direction.x * movementUnit, direction.y * movementUnit, 0.0f };

		if (canMoveTo(newPosition))
		{
			owner.setPosition(newPosition);
		}

		direction = Vector2::zero;

		needUpdate = false;
	}
}

bool TileGridInputComponent::canMoveTo(Vector3 targetPositionP)
{
	if (levelLayout.description.size() == 0) return false;

	int targetIndex = levelLayout.worldCoordinatesToIndex(targetPositionP);
	int tileType = levelLayout.description[targetIndex];

	if (tileType == TileType::OBSTACLE) return false;

	if (tileType == TileType::LIMIT) {
		owner.setState(Actor::ActorState::Out);
	}

	return true;
}

void TileGridInputComponent::setLevelLayout(Layout layoutP) {

	levelLayout = layoutP;
}
