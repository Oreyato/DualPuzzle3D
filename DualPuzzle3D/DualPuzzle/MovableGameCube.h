#pragma once
#include "GameCube.h"

#include "TileGridInputComponent.h"


enum Type
{
    A,
    B
};

class MovableGameCube :
    public GameCube
{
public:
    MovableGameCube() = delete;
    MovableGameCube(float widthP, float heightP, int typeP);

    TileGridInputComponent* getTileGridInputComponent();

    inline Type getType() { return type; }
    inline void setType(Type typeP) { type = typeP; }

protected:
    TileGridInputComponent* tileGridInputComponent;

    Type type;
};
