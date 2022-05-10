#include "Human.h"

#include "World.h"

Human::Human(World* wrld, Position pos, char typ, int cldown, int str, int init)
	:Animal(wrld, pos, typ, cldown, str, init){

}

bool Human::action(ITER it) {
	world->draw_a_human_world(it);
	Position new_position = move(position);
	new_position = special_action(new_position);


	cooldown--;
	if (new_position != position) {
		ITER defender = world->get_organism(new_position);
		int result = (*defender)->collision(it);
		if (result == 1) {
			if ((*defender)->get_type() != '_') {
				string to_log = "Czlowiek zabil ";
				to_log.push_back((*defender)->get_type());
				world->set_log(to_log);
			}

			world->kill_organism(defender);
			world->add_organism('_', position);
			position = new_position;
			world->add_organism_to_tab(it);

			return false;
		}
		else if (result == -1) {
			string to_log = "Czlowiek zginal po zjedzeniu ";
			to_log.push_back((*defender)->get_type());
			world->set_log(to_log);

			world->kill_organism(defender);
			world->add_organism('_', position);
			world->add_organism('_', new_position);

			return true;
		}
		else {
			string to_log = "Czlowiek zginal atakujac ";
			to_log.push_back((*defender)->get_type());
			world->set_log(to_log);

			world->add_organism('_', position);
			return true;
		}
		
	}
	else
		return false;
}
int Human::collision(ITER attacker) {
	if (special_collision(attacker)) {
		string to_log = "Czlowiek zostal zabity przez: ";
		to_log.push_back((*attacker)->get_type());
		world->set_log(to_log);

		return 1;
	}
	else {
		if ((*attacker)->get_strength() >= strength) {
			string to_log = "Czlowiek zostal zabity przez: ";
			to_log.push_back((*attacker)->get_type());
			world->set_log(to_log);

			return 1;
		}
		else {
			string to_log = "Czlowiek przezyl spotkanie z: ";
			to_log.push_back((*attacker)->get_type());
			world->set_log(to_log);

			return 0;
		}
	}
}

Position Human::special_action(Position new_pos) {
	if (cooldown >= 3 && cooldown <= 5)
		new_pos = move(new_pos);
	else if (cooldown >= 1 && cooldown <= 2) {
		if (rand() % 2 == 0)
			new_pos = move(new_pos);
	}

	return new_pos;
}

Position Human::move(Position pos) {
	Position new_pos = pos;
	char where;
	bool test;

	do {
		where = _getch();
		where = toupper(where);
		
		test = false;
		switch (where) {
		case 'R':
			if (cooldown <= -5) {
				cooldown = 5;
				world->set_log("Czlowiek wlaczyl umiejetnosc specjalna");
			}
			test = true;
			break;
		case 'D':
			new_pos += east;
			break;
		case 'E':
			new_pos += north_east;
			break;
		case 'W':
			new_pos += north;
			break;
		case 'Q':
			new_pos += north_west;
			break;
		case 'A':
			new_pos += west;
			break;
		case 'Z':
			new_pos += south_west;
			break;
		case 'X':
			new_pos += south;
			break;
		case 'C':
			new_pos += south_east;
			break;
		default:
			test = true;
			break;
		}
	} while (test);

	if (check_position(new_pos))
		return new_pos;
	else
		return move(pos);
}