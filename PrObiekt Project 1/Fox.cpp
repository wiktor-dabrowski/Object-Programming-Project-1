#include "Fox.h"

#include "World.h"

Fox::Fox(World* wrld, Position pos, char typ, int cldown, int str, int init)
	:Animal(wrld, pos, typ, cldown, str, init) {

}

Position Fox::special_action(Position new_pos) {
	ITER enemy = world->get_organism(new_pos);
	if ((*enemy)->get_strength() > strength)
		new_pos = position;

	return new_pos;
}