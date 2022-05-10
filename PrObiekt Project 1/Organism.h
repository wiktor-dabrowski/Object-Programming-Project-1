#pragma once
#include <cstdlib>
#include <iostream>
#include <list>
#include <conio.h>
#include <string>

#include "Structures.h"

using namespace std;

class World;

class Organism
{
protected:
	int strength, initiative;
	Position position;
	World* world;
	char type;
public:
	Organism(World*, Position, char = '?', int = 0, int = 0);
	~Organism();

	virtual bool action(ITER) = 0;  //return true if organism is killed
	virtual int collision(ITER) = 0;  //return 1 if organism is killed, 0 if isnt, -1 if both are killed
	virtual void draw();

	virtual int get_strength();
	virtual void set_strength(int);
	virtual int get_initiative();
	virtual Position get_position();
	virtual void set_position(Position);
	virtual char get_type();
protected:
	Position where_next(Position, int = rand() % 8);
	bool check_position(Position);
};