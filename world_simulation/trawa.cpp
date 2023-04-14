#include "trawa.h"

using namespace std;

Trawa::Trawa(Point&& _position, World* _world) {
	position = _position;
	ID = 't';
	world = _world;
	newPlantPosition = { 0, 0 };

	power = 0;
}

Organism* Trawa::newObj(Point&& _position, World* _world) {
	Organism* obj = new Trawa(move(_position), _world);
	return obj;
}