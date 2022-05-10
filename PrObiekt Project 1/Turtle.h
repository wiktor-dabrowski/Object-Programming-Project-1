#pragma once
#include "Animal.h"

using namespace std;

class Turtle :
    public Animal
{
public:
    Turtle(World*, Position, char = 'T', int = 1, int = 2, int = 1);

    virtual int collision(ITER) override;
protected:
    virtual Position special_action(Position) override;
    virtual bool special_collision(ITER) override;
};

