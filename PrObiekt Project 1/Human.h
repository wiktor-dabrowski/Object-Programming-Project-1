#pragma once
#include "Animal.h"

using namespace std;

class Human :
    public Animal
{
public:
    Human(World*, Position, char = '!', int = -5, int = 5, int = 4);

    virtual bool action(ITER) override;
    virtual int collision(ITER) override;
protected:
    virtual Position special_action(Position) override;
    virtual Position move(Position);
};

