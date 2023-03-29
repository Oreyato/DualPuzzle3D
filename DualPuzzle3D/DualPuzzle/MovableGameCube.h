#pragma once
#include "GameCube.h"

#include "TileGridInputComponent.h"


class MovableGameCube :
    public GameCube
{
public:
    MovableGameCube() = delete;
    MovableGameCube(float widthP, float heightP, int typeP);

    TileGridInputComponent* getTileGridInputComponent();

private:
    TileGridInputComponent* tileGridInputComponent;
};
