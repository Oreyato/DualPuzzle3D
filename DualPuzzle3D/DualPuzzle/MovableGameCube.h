#pragma once
#include "GameCube.h"


class MovableGameCube :
    public GameCube
{
public:
    MovableGameCube() = delete;
    MovableGameCube(float widthP, float heightP, int typeP);

};

