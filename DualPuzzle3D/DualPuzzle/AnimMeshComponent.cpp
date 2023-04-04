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
	}
}

void AnimMeshComponent::draw(Shader& shader)
{
	if (mesh) {
		if (animTextures.size() > 0) {
			Matrix4 wt = owner.getWorldTransform();
			shader.setMatrix4("uWorldTransform", wt);
			shader.setFloat("uSpecPower", mesh->getSpecularPower());
			Texture* t = animTextures[static_cast<int>(currentFrame)];
			if (t)
			{
				t->setActive();
			}
			VertexArray* va = mesh->getVertexArray();
			va->setActive();
			glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
		}
		else {
			Matrix4 wt = owner.getWorldTransform();
			shader.setMatrix4("uWorldTransform", wt);
			shader.setFloat("uSpecPower", mesh->getSpecularPower());
			Texture* t = mesh->getTexture(textureIndex);
			if (t)
			{
				t->setActive();
			}
			VertexArray* va = mesh->getVertexArray();
			va->setActive();
			glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
