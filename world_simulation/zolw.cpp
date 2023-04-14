#include "zolw.h"

using namespace std;

Zolw::Zolw(Point&& p, World* _world) {
	position = p;
	world = _world;
	power = 2;
	initiative = 1;
	ID = 'Z';
}

Organism* Zolw::newObj(Point&& _position, World* _world) {
	Organism* obj = new Zolw(move(_position), _world);
	return obj;
}

void Zolw::action() {
	if ((rand() % 100) < 75) return;
	Animal::action();
}

bool Zolw::defence(Organism* _other) {
	return _other->getPower() < 5;
}

