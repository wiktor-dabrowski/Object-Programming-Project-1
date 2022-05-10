#include "Grass.h"

Grass::Grass(World* wrld, Position pos, char typ, int chnce, int str, int init)
	:Plant(wrld, pos, typ, chnce, str, init) {

}

bool Grass::action(ITER it) {

	return false;
}