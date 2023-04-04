#pragma once
#include "GameCube.h"

#include "TileGridInputComponent.h"



class MovableGameCube :
    public GameCube
{
public:
    enum Type
    {
        A,
        B
    };

    MovableGameCube() = delete;
    MovableGameCube(float widthP, float heightP, int typeP);

    TileGridInputComponent* getTileGridInputComponent();

    inline Type getType() { return type; }
    inline void setType(Type typeP) { type = typeP; }

    inline Vector3 getPreviousPosition() { return previousPosition; }

protected:
    TileGridInputComponent* tileGridInputComponent;

    Vector3 previousPosition{ 0.0f, 0.0f, 0.0f };
    Type type;
};
