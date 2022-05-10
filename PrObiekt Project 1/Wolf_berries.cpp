#include "Wolf_berries.h"

Wolf_berries::Wolf_berries(World* wrld, Position pos, char typ, int chnce, int str, int init)
	:Plant(wrld, pos, typ, chnce, str, init) {

}

bool Wolf_berries::special_collision(ITER attacker) {
	if (((*attacker)->get_type() >= 'A' && (*attacker)->get_type() <= 'Z') || (*attacker)->get_type() == '!')
		return true;
	else
		return false;
}