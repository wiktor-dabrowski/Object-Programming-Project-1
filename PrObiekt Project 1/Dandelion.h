#pragma once
#include "Plant.h"

using namespace std;

class Dandelion :
    public Plant
{
public:
    Dandelion(World*, Position, char = 'd', int = 5, int = 0, int = 0);
protected:
    virtual void special_action() override;
};

