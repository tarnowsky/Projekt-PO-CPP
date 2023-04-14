#include "lis.h"
using namespace std;

Lis::Lis(Point&& p, World* _world) {
	position = p;
	world = _world;
	power = 3;
	initiative = 7;
	ID = 'L';
}

Organism* Lis::newObj(Point&& _position, World* _world) {
	Organism* obj = new Lis(move(_position), _world);
	return obj;
}

bool Lis::fight(Organism* _other) {
	if (power >= _other->getPower()) {
		Organism::eliminate(_other);
		return true;
	}
	else return false;
}