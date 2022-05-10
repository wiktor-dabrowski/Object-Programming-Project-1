#include "Turtle.h"

Turtle::Turtle(World* wrld, Position pos, char typ, int cldown, int str, int init)
	:Animal(wrld, pos, typ, cldown, str, init) {

}

int Turtle::collision(ITER attacker) {
	if ((*attacker)->get_type() == get_type()) {
		breeding(attacker);
		cooldown = 5;
		return 0;
	}
	else {
		if (special_collision(attacker))
			return 1;
		else {
			if ((*attacker)->get_strength() >= strength && (*attacker)->get_strength() >= 5)
				return 1;
			else
				return 0;
		}
	}
}

Position Turtle::special_action(Position new_pos) {
	if (rand() % 4 < 3)
		new_pos = position;

	return new_pos;
}
bool Turtle::special_collision(ITER attacker) {
	if ((*attacker)->get_strength() >= 5)
		return true;
	else
		return false;
}