#include "TileGridInputComponent.h"

#include "InputSystem.h"
#include "Actor.h"
#include "Consts.h"


TileGridInputComponent::TileGridInputComponent(Actor* ownerP) :
	Component{ ownerP, 10 },
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
	}
	if (inputState.keyboard.getKeyState(downKey) == ButtonState::Pressed) {
		direction.y = 1;
	}
	if (inputState.keyboard.getKeyState(leftKey) == ButtonState::Pressed) {
		direction.x = -1;
	}
	if (inputState.keyboard.getKeyState(rightKey) == ButtonState::Pressed) {
		direction.x = 1;
	}

	Vector3 newPosition = owner.getPosition();
	newPosition += Vector3{ direction.x * movementUnit, direction.y * movementUnit, 0.0f };

	owner.setPosition(newPosition);

	direction = Vector2::zero;
}
