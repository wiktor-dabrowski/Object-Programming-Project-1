#include "Organism.h"
#include "World.h"

Organism::Organism(World* wrld, Position pos, char typ, int str, int init)
	:initiative(init), strength(str), position(pos), world(wrld), type(typ) {
}
Organism::~Organism() {

}

void Organism::draw() {
	cout << type;
}

int Organism::get_strength() {
	return strength;
}
void Organism::set_strength(int str) {
	strength = str;
}
int Organism::get_initiative() {
	return initiative;
}
Position Organism::get_position() {
	return position;
}
void Organism::set_position(Position pos) {
	position = pos;
}
char Organism::get_type() {
	return type;
}

Position Organism::where_next(Position pos, int where_next) {
	Position to_return;
	do {
		to_return = pos;
		switch (where_next) {
		case 0:
			to_return = pos + east;
			break;
		case 1:
			to_return = pos + north_east;
			break;
		case 2:
			to_return = pos + north;
			break;
		case 3:
			to_return = pos + north_west;
			break;
		case 4:
			to_return = pos + west;
			break;
		case 5:
			to_return = pos + south_west;
			break;
		case 6:
			to_return = pos + south;
			break;
		case 7:
			to_return = pos + south_east;
			break;
		}
		where_next = rand() % 8;
	} while (!check_position(to_return));

	return to_return;
}

bool Organism::check_position(Position pos) {
	Position world_size = world->get_size();
	return (pos.x >= 0 && pos.x < world_size.x && pos.y >= 0 && pos.y < world_size.y);
}