#pragma once
#include "Animal.h"

using namespace std;

class Antelope :
    public Animal
{
public:
    Antelope(World*, Position, char = 'A', int = 1, int = 4, int = 4);
protected:
    virtual Position special_action(Position) override;
    virtual bool special_collision(ITER) override;
};

