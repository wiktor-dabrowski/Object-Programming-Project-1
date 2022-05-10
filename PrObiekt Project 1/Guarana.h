#pragma once
#include "Plant.h"

using namespace std;

class Guarana :
    public Plant
{
public:
    Guarana(World*, Position, char = 'g', int = 5, int = 0, int = 0);
protected:
    virtual bool special_collision(ITER) override;
};

