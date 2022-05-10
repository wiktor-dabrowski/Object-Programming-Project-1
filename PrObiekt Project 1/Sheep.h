#pragma once
#include "Animal.h"

using namespace std;

class Sheep :
    public Animal
{
public:
    Sheep(World*, Position, char = 'S', int = 1, int = 4, int = 4);
};

