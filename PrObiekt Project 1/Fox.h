#pragma once
#include "Animal.h"

using namespace std;

class Fox :
    public Animal
{
public:
    Fox(World*, Position, char = 'F', int = 1, int = 3, int = 7);
protected:
    virtual Position special_action(Position) override;
};

