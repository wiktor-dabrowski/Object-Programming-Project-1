#include "Guarana.h"
Guarana::Guarana(World* wrld, Position pos, char typ, int chnce, int str, int init)
	:Plant(wrld, pos, typ, chnce, str, init) {

}

bool Guarana::special_collision(ITER attacker) {
	if (((*attacker)->get_type() >= 'A' && (*attacker)->get_type() <= 'Z') || (*attacker)->get_type() == '!')
		(*attacker)->set_strength((*attacker)->get_strength() + 3);

	return false;
}