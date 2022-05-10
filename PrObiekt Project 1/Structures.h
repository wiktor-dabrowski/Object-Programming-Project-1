#pragma once

#define ITER list<Organism*>::iterator

struct Position {
	int x, y;
	Position(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}
	Position operator+(Position a) {
		Position result = Position(x, y);
		result.x += a.x;
		result.y += a.y;

		return result;
	}
	void operator=(Position a) {
		x = a.x;
		y=a.y;
	}

	void operator+=(Position a) {
		x += a.x;
		y += a.y;
	}
	bool operator==(Position a) {
		if (this->x == a.x && this->y == a.y)
			return true;
		else
			return false;
	}
	bool operator!=(Position a) {
		return !(*this == a);
	}
};
/* table look
				/\
				||
				|| north
<--- west	  0_0 1_0 2_0 3_0 4_0		---> east
			  0_1 1_1 2_1 3_1 4_1 
			  0_2 1_2 2_2 3_2 4_2
				||
				||
				\/ south

*/

const Position east = Position(1, 0);
const Position north_east = Position(1, -1);
const Position north = Position(0, -1);
const Position north_west = Position(-1, -1);
const Position west = Position(-1, 0);
const Position south_west = Position(-1, 1);
const Position south = Position(0, 1);
const Position south_east = Position(1, 1);

struct default_settings {
	int width = 5;
	int height = 10;
	int number_of_different_organisms = 10;
	int* tab;

	default_settings() {
		tab = new int[number_of_different_organisms];

		tab[0] = 3;// antelope
		tab[1] = 3;//fox
		tab[2] = 5;//sheep
		tab[3] = 3;//turtle
		tab[4] = 2;//wolf

		tab[5] = 3;//dandelion
		tab[6] = 5;//guarana
		tab[7] = 2;//sosnowskys_hogweed
		tab[8] = 3;//wolf_berries

		tab[9] = 1;///human
	}

	~default_settings() {
		delete[] tab;
	}
};