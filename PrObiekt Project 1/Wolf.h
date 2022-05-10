#pragma once
#include "Animal.h"

using namespace std;

class Wolf :
    public Animal
{
public:
    Wolf(World*, Position, char = 'W', int = 1, int = 9, int = 5);
};

