#pragma once
#include "Plant.h"

using namespace std;

class Wolf_berries :
    public Plant
{
public:
    Wolf_berries(World*, Position, char = 'w', int = 5, int = 99, int = 0);
protected:
    virtual bool special_collision(ITER) override;
};

