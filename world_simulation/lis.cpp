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
	if (_other->defence(this)) return false;
	if (power >= _other->getPower()) {
		if (!_other->escape()) {
			_other->afterDeathEffect(this);
			world->addInfo("Eliminacja (" +
				to_string(_other->getPosition().x) + ", " + to_string(_other->getPosition().y) + ")"
			);
			Organism::eliminate(_other);
		}
		return true;
	}
	else return false;
}