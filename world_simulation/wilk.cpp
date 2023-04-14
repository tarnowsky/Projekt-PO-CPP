#include "wilk.h"

using namespace std;

Wilk::Wilk(Point&& p, World* _world) {
	position = p;
	world = _world;
	power = 9;
	initiative = 5;
	ID = 'W';
}

Organism* Wilk::newObj(Point&& _position, World* _world) {
	Organism* obj = new Wilk(move(_position), _world);
	return obj;
}
