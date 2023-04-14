#include "mlecz.h"

using namespace std;

Mlecz::Mlecz(Point&& _position, World* _world) {
	position = _position;
	ID = 'm';
	world = _world;
	newPlantPosition = { 0, 0 };

	power = 0;
}

Organism* Mlecz::newObj(Point&& _position, World* _world) {
	Organism* obj = new Mlecz(move(_position), _world);
	return obj;
}

bool Mlecz::tryingToPlant() {
	for (int i = 0; i < 3; i++)
		if ((rand() % 10) < 5) return true;
	return false;
}

