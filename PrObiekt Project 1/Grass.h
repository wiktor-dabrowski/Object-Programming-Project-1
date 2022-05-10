#pragma once
#include "Plant.h"

using namespace std;

class Grass :
    public Plant
{
public:
    Grass(World*, Position, char = '_', int = 5, int = 0, int = 0);
    virtual bool action(ITER) override;
};

