
#pragma once
#include "Organism.h"
#include "Animal.h"

using namespace std;

class Plant :
    public Organism
{
protected:
	int chance_of_spread;
public:
	Plant(World*, Position, char = '*', int = 5, int = 0, int = 0);
	~Plant();
	
	virtual bool action(ITER) override;  //return true if plant is killed
	virtual int collision(ITER) override;  //return 1 if plant is killed, 0 if isnt(never), -1 if attacker and plant are killed

	virtual int get_chance_of_spread();
protected:
	virtual void spreading();
	virtual void special_action();
	virtual bool special_collision(ITER);   //return true if attacker is killed
};

