#include "AnimMeshComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"


AnimMeshComponent::AnimMeshComponent(Actor* ownerP) :
	MeshComponent{ ownerP },
	currentFrame{ 0.0f },
	animFPS{ 0.0f }
{
}

AnimMeshComponent::~AnimMeshComponent()
{
}

void AnimMeshComponent::setAnimTextures(const std::vector<Texture*>& texturesP)
{
	animTextures = texturesP;

	if (animTextures.size() > 0) {
		currentFrame = 0.0f;
		
		mesh->setTexture(animTextures[0]);
	}
}

void AnimMeshComponent::setAnimFPS(float animFPSP)
{
	animFPS = animFPSP;
}

void AnimMeshComponent::update(float dt)
{
	MeshComponent::update(dt);

	if (animTextures.size() > 0)
	{
		currentFrame += animFPS * dt;
		while (currentFrame >= animTextures.size())
		{
			currentFrame -= animTextures.size();
		}
		mesh->setTexture(animTextures[static_cast<int>(currentFrame)]);
	}
}
