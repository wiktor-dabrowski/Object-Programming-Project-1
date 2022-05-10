#include "Animal.h"

#include "World.h"

Animal::Animal(World* wrld, Position pos, char typ, int cldown, int str, int init)
:Organism(wrld, pos, typ, str, init), cooldown(cldown){

}
Animal::~Animal() {

}

bool Animal::action(ITER it) {
	Position new_position = where_next(position);
	new_position = special_action(new_position);
	cooldown--;
	if (new_position != position) {
		ITER defender = world->get_organism(new_position);
		int result = (*defender)->collision(it);
		if (result == 1) {
			world->kill_organism(defender);
			world->add_organism('_', position);
			position = new_position;
			world->add_organism_to_tab(it);

			return false;
		}
		else if (result == -1) {
			world->kill_organism(defender);
			world->add_organism('_', position);
			world->add_organism('_', new_position);

			return true;
		}
		else
			return false;
	}
	else
		return false;
}
int Animal::collision(ITER attacker) {
	if ((*attacker)->get_type() == get_type()) {
		breeding(attacker);
		cooldown = 5;
		return 0;
	}
	else {
		if (special_collision(attacker))
			return 1;
		else {
			if ((*attacker)->get_strength() >= strength)
				return 1;
			else
				return 0;
		}
	}

}

int Animal::get_cooldown() {

	return cooldown;
}


void Animal::breeding(ITER attacker) {
	if (cooldown <= 0) {
		Position child_position;
		do {
			child_position = where_next(position);
		} while (child_position == (*attacker)->get_position());

		ITER defender = world->get_organism(child_position);
		if ((*defender)->get_type() == '_') {
			world->add_organism((*attacker)->get_type(), child_position);
			world->kill_organism(defender);
		}
		else if ((*defender)->get_type() >= 'a' && (*defender)->get_type() <= 'z') {
			int result = (*defender)->collision(attacker);
			if (result == -1) {
				world->add_organism('_', child_position);
				world->kill_organism(defender);
			}
		}
	}
}
Position Animal::special_action(Position new_pos) {

	return new_pos;
}
bool Animal::special_collision(ITER attacker) {

	return false;
}