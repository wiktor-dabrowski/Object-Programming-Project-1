#pragma once
#include "Organism.h"
#include "Plant.h"

using namespace std;

class Animal :
    public Organism
{
protected:
    int cooldown;
public:
	Animal(World*, Position, char = '^', int = 1, int = 0, int = 0);
	~Animal();

	virtual bool action(ITER) override;  //return true if animal is killed
	virtual int collision(ITER) override;  //return 1 if animal is killed, 0 if isnt killed, -1 if animal and attacker are killed

	virtual int get_cooldown();
protected:
	virtual void breeding(ITER);
	virtual Position special_action(Position);
	virtual bool special_collision(ITER);   //return true if defender is killed
};

