#include "World.h"

World::World(){
	srand(time(NULL));
	system("COLOR 2F");

	fstream save;
	save.open("save.txt", ios::in);
	if (save.is_open()) {
		cout << "Jesli chcesz stworzyc nowa gre, kliknij N" << endl;
		cout << "Jesli chcesz wczytac gre, kliknij L " << endl;
		bool test = false;
		char command;
		do {
			test = false;
			command = _getch();
			command = toupper(command);
			if (command == 'N')
				create_game();
			else if (command == 'L')
				load_game(&save);
			else
				test = true;
		} while (test);
	}
	else
		create_game();

	save.close();
}
World::~World() {
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++)
			kill_organism(tab[i][j]);
	}
	for (int i = 0; i < size.x; i++)
		delete[] tab[i];
	delete[] tab;
}

void World::game() {
	while (is_end) {
		draw_a_world();
		bool test = false;
		char command;
		do {
			test = false;
			command = _getch();
			command = toupper(command);
			if (command == 27)  //ESC==27
				is_end = false;
			else if (command == 'S')
				make_turn();
			else
				test = true;
		} while (test);
	}
	save_game();
}
void World::make_turn() {
	ITER it = lst.begin();
	while (it != lst.end()) {
		bool is_killed = (*it)->action(it);
		if (is_killed) {
			kill_organism(it++);
		}
		else
			it++;
	}

	round_nr++;
}
void World::draw_a_human_world(ITER human) {
	system("CLS");

	cout << "   ____         _                      _          _    " << endl;
	cout << "  / ___|  ____ | |   ___   __      __ (_)   ___  | | __" << endl;
	cout << " | |     |_  / | |  / _ \\  \\ \\ /\\ / / | |  / _ \\ | |/ /" << endl;
	cout << " | |___   / /  | | | (_) |  \\ V  V /  | | |  __/ |   < " << endl;
	cout << "  \\____| /___| |_|  \\___/    \\_/\\_/   |_|  \\___| |_|\\_\\" << endl;
	cout << "                                                       " << endl;

	draw_a_world_helper();

	Human* humanoid = dynamic_cast<Human*>(*human);
	if (humanoid && humanoid->get_cooldown() <= -5)
		cout << "R - aktywuj umiejetnosc specjalna" << endl;
	else if (humanoid && humanoid->get_cooldown() > 2)
		cout << " Umiejetnosc specjalna jest aktywna ze 100% szans" << endl;
	else if (humanoid && humanoid->get_cooldown() > 0)
		cout << " Umiejetnosc specjalna jest aktywna z 50% szans" << endl;

	cout << "Q W E" << endl << "A   D  -  sterowanie" << endl << "Z X C" << endl;
}
ITER World::get_organism(Position ps) {
	return tab[ps.x][ps.y];
}
void World::add_organism(char org_type, Position pos) {
	Organism* org = create_organism(org_type, pos);
	if (lst.empty()) {
		lst.push_front(org);
		tab[pos.x][pos.y] = lst.begin();
	}
	else if (lst.size() == 1) {
		if ((*lst.begin())->get_initiative() >= org->get_initiative()) {
			lst.push_back(org);
			tab[pos.x][pos.y] = --lst.end();
		}
		else {
			lst.push_front(org);
			tab[pos.x][pos.y] = lst.begin();
		}
	}
	else {
		if ((org->get_type() >= 'a' && org->get_type() <= 'z') || org->get_type() == '_') {
			lst.push_back(org);
			tab[pos.x][pos.y] = --lst.end();
		}
		else {
			ITER i;
			for (i = lst.begin(); i != lst.end(); i++) {
				if ((*i)->get_initiative() < org->get_initiative())
					break;
			}
			tab[pos.x][pos.y] = lst.insert(i, org);
		}
	}
}
void World::add_organism_to_tab(ITER to_add) {
	tab[(*to_add)->get_position().x][(*to_add)->get_position().y] = to_add;
}
Position World::get_size() {
	return size;
}
void World::kill_organism(ITER to_kill) {
	delete (*to_kill);
	lst.erase(to_kill);
}
void World::set_log(string to_log) {
	for (int i = 3; i >= 0; i--) {
		log[i + 1] = log[i];
	}
	log[0] = to_log;
}

void World::create_game() {
	default_settings settings;
	fstream settings_file;
	settings_file.open("settings.txt", ios::in);
	int number_of_all_organisms = 0;
	if (settings_file.is_open()) {
		settings_file >> settings.width >> settings.height;
		for (int i = 0; i < settings.number_of_different_organisms; i++) {
			settings_file >> settings.tab[i];
			number_of_all_organisms += settings.tab[i];
		}
	}
	settings_file.close();
	if (number_of_all_organisms > settings.height * settings.width) {
		throw "Wiecej organizmow niz pol tablicy";
	}
		

	size = Position(settings.width, settings.height);
	tab = new ITER* [size.x];
	for (int i = 0; i < size.x; i++)
		tab[i] = new ITER[size.y];
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++)
			add_organism('_', Position(i, j));
	}

	for (int i = 0; i < settings.number_of_different_organisms; i++) {
		for (int j = 0; j < settings.tab[i]; j++) {
			Position to_add = Position(rand() % size.x, rand() % size.y);
			if ((*get_organism(to_add))->get_type() == '_') {
				kill_organism(get_organism(to_add));
				add_organism(i, to_add);
			}
			else {
				to_add = Position(rand() % size.x, rand() % size.y);
				j--;
			}
		}
	}
}
void World::load_game(fstream* save) {
	*save >> size.x >> size.y;
	*save >> round_nr;
	char typ;
	Position pos;
	int cldown_spread, str, init;

	tab = new ITER * [size.x];
	for (int i = 0; i < size.x; i++)
		tab[i] = new ITER[size.y];

	for (int i = 0; i < size.x * size.y; i++) {
		*save >> typ >> pos.x >> pos.y >> cldown_spread >> str >> init;
		Organism* org = create_organism(typ, pos, cldown_spread, str, init);
		lst.push_back(org);
		add_organism_to_tab(--lst.end());
	}

	getline(*save, log[0]);
	for (int i = 0; i < 5; i++) {
		getline(*save, log[i]);
	}
		
}
void World::save_game() {
	fstream save;
	save.open("save.txt", ios::out);
	save << size.x << " " << size.y << endl;
	save << round_nr << endl;

	for (ITER it = lst.begin(); it != lst.end(); it++) {
		save << (*it)->get_type() << " " << (*it)->get_position().x << " " << (*it)->get_position().y << " ";
		Plant* plant = dynamic_cast<Plant*>(*it);
		if (plant)
			save << plant->get_chance_of_spread() << " ";
		Animal* animal = dynamic_cast<Animal*>(*it);
		if(animal)
			save << animal->get_cooldown() << " ";
		save << (*it)->get_strength() << " " << (*it)->get_initiative() << endl;
	}

	for (int i = 0; i < 5; i++)
		save << log[i] << endl;

	save.close();
}

Organism* World::create_organism(char typ, Position pos) {
	Organism* to_return;
	switch (typ) {
	case '_':
		to_return = new Grass(this, pos);
		break;
	case 'A':
		to_return = new Antelope(this, pos);
		break;
	case 'F':
		to_return = new Fox(this, pos);
		break;
	case 'S':
		to_return = new Sheep(this, pos);
		break;
	case 'T':
		to_return = new Turtle(this, pos);
		break;
	case 'W':
		to_return = new Wolf(this, pos);
		break;
	case 'd':
		to_return = new Dandelion(this, pos);
		break;
	case 'g':
		to_return = new Guarana(this, pos);
		break;
	case 's':
		to_return = new Sosnowskys_hogweed(this, pos);
		break;
	case 'w':
		to_return = new Wolf_berries(this, pos);
		break;
	case '!':
		to_return = new Human(this, pos);
		break;
	case 0:
		to_return = create_organism('A', pos);
		break;
	case 1:
		to_return = create_organism('F', pos);
		break;
	case 2:
		to_return = create_organism('S', pos);
		break;
	case 3:
		to_return = create_organism('T', pos);
		break;
	case 4:
		to_return = create_organism('W', pos);
		break;
	case 5:
		to_return = create_organism('d', pos);
		break;
	case 6:
		to_return = create_organism('g', pos);
		break;
	case 7:
		to_return = create_organism('s', pos);
		break;
	case 8:
		to_return = create_organism('w', pos);
		break;
	case 9:
		to_return = create_organism('!', pos);
		break;
	default:
		to_return = new Plant(this, pos);
	}

	return to_return;
}
Organism* World::create_organism(char typ, Position pos, int cldown_spread, int str, int init) {
	Organism* to_return;

	switch (typ) {
	case '_':
		to_return = new Grass(this, pos, typ, cldown_spread, str, init);
		break;
	case 'A':
		to_return = new Antelope(this, pos, typ, cldown_spread, str, init);
		break;
	case 'F':
		to_return = new Fox(this, pos, typ, cldown_spread, str, init);
		break;
	case 'S':
		to_return = new Sheep(this, pos, typ, cldown_spread, str, init);
		break;
	case 'T':
		to_return = new Turtle(this, pos, typ, cldown_spread, str, init);
		break;
	case 'W':
		to_return = new Wolf(this, pos, typ, cldown_spread, str, init);
		break;
	case 'd':
		to_return = new Dandelion(this, pos, typ, cldown_spread, str, init);
		break;
	case 'g':
		to_return = new Guarana(this, pos, typ, cldown_spread, str, init);
		break;
	case 's':
		to_return = new Sosnowskys_hogweed(this, pos, typ, cldown_spread, str, init);
		break;
	case 'w':
		to_return = new Wolf_berries(this, pos, typ, cldown_spread, str, init);
		break;
	case '!':
		to_return = new Human(this, pos, typ, cldown_spread, str, init);
		break;
	default:
		to_return = new Plant(this, pos);
	}

	return to_return;
}

void World::draw_a_world() {
	system("CLS");

	cout << "  ____               _           _       _____             _                               _   " << endl;
	cout << " / ___|  __      __ (_)   __ _  | |_    |__  / __      __ (_)   ___   _ __   ____   __ _  | |_ " << endl;
	cout << " \\___ \\  \\ \\ /\\ / / | |  / _` | | __|     / /  \\ \\ /\\ / / | |  / _ \\ | '__| |_  /  / _` | | __|" << endl;
	cout << "  ___) |  \\ V  V /  | | | (_| | | |_     / /_   \\ V  V /  | | |  __/ | |     / /  | (_| | | |_ " << endl;
	cout << " |____/    \\_/\\_/   |_|  \\__,_|  \\__|   /____|   \\_/\\_/   |_|  \\___| |_|    /___|  \\__,_|  \\__|" << endl;
	cout << "                                                                                               " << endl;

	draw_a_world_helper();

	cout << "Wiktor Dabrowski, s184392" << endl << endl;
	cout << "S - nowa tura" << endl;
	cout << "ESC - wyjdz z gry" << endl;
}
void World::draw_a_world_helper() {
	cout << "Tura nr " << round_nr << endl;
	cout << char(201);
	for (int i = 0; i < size.x * 2 + 1; i++)
		cout << char(205);
	cout << char(187) << endl;

	for (int i = 0; i < size.y; i++) {
		cout << char(186);
		cout << " ";
		for (int j = 0; j < size.x; j++) {
			(*tab[j][i])->draw();
			cout<<" ";
		}
		cout << char(186) <<endl;
	}

	cout << char(204);
	for (int i = 0; i < size.x * 2 + 1; i++)
		cout << char(205);
	cout << char(188) << endl;

	for (int i = 0; i < 5; i++)
		cout << char(186) << " " << log[i] << endl;

	cout << endl;
}