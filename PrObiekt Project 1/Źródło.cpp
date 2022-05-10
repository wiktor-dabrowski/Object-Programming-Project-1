#include "World.h"

using namespace std;

int main() {
	World* world = new World;
	world->game();

	delete world;
	return 0;
}