#include "Antelope.h"

#include "World.h"

Antelope::Antelope(World* wrld, Position pos, char typ, int cldown, int str, int init)
	:Animal(wrld, pos, typ, cldown, str, init) {

}

Position Antelope::special_action(Position new_pos) {
	new_pos = where_next(new_pos);

	return new_pos;
}
bool Antelope::special_collision(ITER attacker) {
	if (rand() % 2 == 0) {
		Position to_move;
		bool is_possible_to_move = false;
		for (int i = 0; i < 8; i++) {
			to_move = where_next(position, i);
			if (check_position(to_move)) {
				ITER org = world->get_organism(to_move);
				if ((*org)->get_type() == '_') {
					is_possible_to_move = true;
					break;
				}
			}
		}

		if (is_possible_to_move) {
			world->kill_organism(world->get_organism(to_move));
			world->add_organism('A', to_move);

			return true;
		}
	}

	return false;
}