#include "Sosnowskys_hogweed.h"

#include "World.h"

Sosnowskys_hogweed::Sosnowskys_hogweed(World* wrld, Position pos, char typ, int chnce, int str, int init)
	:Plant(wrld, pos, typ, chnce, str, init) {

}

void Sosnowskys_hogweed::special_action() {
	for (int i = 0; i < 8; i++) {
		Position pos = where_next(position, i);
		ITER to_kill = world->get_organism(pos);
		if (((*to_kill)->get_type() >= 'A' && (*to_kill)->get_type() <= 'Z') || (*to_kill)->get_type()=='!') {
			if ((*to_kill)->get_type() == '!')
				world->set_log("Czlowiek zostal zabity przez s");
			world->kill_organism(to_kill);
			world->add_organism('_', pos);
		}
	}
}
bool Sosnowskys_hogweed::special_collision(ITER attacker) {
	if (((*attacker)->get_type() >= 'A' && (*attacker)->get_type() <= 'Z') || (*attacker)->get_type() == '!')
		return true;
	else
		return false;
}