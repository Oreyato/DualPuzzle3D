#pragma once
#include "MeshComponent.h"

#include <vector>

#include "Texture.h"


class AnimMeshComponent :
    public MeshComponent
{
public:
    AnimMeshComponent(Actor* ownerP);
    virtual ~AnimMeshComponent();

    AnimMeshComponent() = delete;
    AnimMeshComponent(const AnimMeshComponent&) = delete;
    AnimMeshComponent& operator=(const AnimMeshComponent&) = delete;

    inline float getAnimFPS() const { return animFPS; }
    void setAnimTextures(const std::vector<Texture*>& texturesP);
    void setAnimFPS(float animFPSP);

    void update(float dt) override;
    void draw(Shader& shader) override;

private:
    std::vector<Texture*> animTextures;

    float currentFrame;
    float maximumFrame;
    float animFPS;
};

