#pragma once
#include "Plant.h"

using namespace std;

class Sosnowskys_hogweed :
    public Plant
{
public:
    Sosnowskys_hogweed(World*, Position, char = 's', int = 0, int = 10, int = 0);
protected:
    virtual void special_action() override;
    virtual bool special_collision(ITER) override;
};

