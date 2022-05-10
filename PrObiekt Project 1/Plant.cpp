#include "Plant.h"

#include "World.h"

Plant::Plant(World* wrld, Position pos, char typ, int chnce, int str, int init)
	:Organism(wrld, pos, typ, str, init), chance_of_spread(chnce) {

}
Plant::~Plant() {

}

bool Plant::action(ITER it) {
	special_action();
	spreading();

	return false;
}
int Plant::collision(ITER attacker) {
	if (special_collision(attacker))
		return -1;
	else
		return 1;
}

int Plant::get_chance_of_spread() {

	return chance_of_spread;
}


void Plant::spreading() {
	if (rand() % 100 < chance_of_spread) {
		Position new_plant_position = where_next(position);
		ITER enemy = world->get_organism(new_plant_position);
		if ((*enemy)->get_type() == '_') {
			world->add_organism(type, new_plant_position);
			world->kill_organism(enemy);
		}
	}
}
void Plant::special_action() {

}

bool Plant::special_collision(ITER attacker) {

	return false;
}