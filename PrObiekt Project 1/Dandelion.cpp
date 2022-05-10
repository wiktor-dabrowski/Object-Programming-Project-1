#include "Dandelion.h"

Dandelion::Dandelion(World* wrld, Position pos, char typ, int chnce, int str, int init)
:Plant(wrld, pos, typ, chnce, str, init){

}

void Dandelion::special_action() {
	spreading();
	spreading();
}