#include "guarana.h"

using namespace std;

Guarana::Guarana(Point&& _position, World* _world) {
	position = _position;
	ID = 'g';
	world = _world;
	newPlantPosition = { 0, 0 };

	power = 0;
}

Organism* Guarana::newObj(Point&& _position, World* _world) {
	Organism* obj = new Guarana(move(_position), _world);
	return obj;
}

void Guarana::afterDeathEffect(Organism* _other) {
	int newPower = _other->getPower();
	newPower += 3;
	_other->setPower(newPower);
}
