#pragma once
#include <list>
#include <iostream>
#include <fstream>

#include "Structures.h"
#include "Organism.h"
#include "Animal.h"
#include "Plant.h"

#include "Human.h"
#include "Grass.h"

#include "Antelope.h"
#include "Fox.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"

#include "Dandelion.h"
#include "Guarana.h"
#include "Sosnowskys_hogweed.h"
#include "Wolf_berries.h"

using namespace std;

class World
{
	Position size;
	list<Organism*> lst;
	ITER** tab;
	bool is_end = true;
	int round_nr = 0;

	string log[5] = {""};
public:
	World();
	~World();

	void game();
	void make_turn();
	void draw_a_human_world(ITER);

	ITER get_organism(Position);
	void add_organism(char, Position);
	void add_organism_to_tab(ITER);
	void kill_organism(ITER);
	Position get_size();
	void set_log(string);
private:
	void create_game();
	void load_game(fstream*);
	void save_game();

	Organism* create_organism(char, Position);
	Organism* create_organism(char, Position, int, int, int);

	void draw_a_world();
	void draw_a_world_helper();
};