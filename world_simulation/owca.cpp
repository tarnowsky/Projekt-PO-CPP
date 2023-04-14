#include "owca.h"
using namespace std;

Owca::Owca(Point&& p, World* _world) {
	position = p;
	world = _world;
	power = 4;
	initiative = 4;
	ID = 'O';
}

Organism* Owca::newObj(Point&& _position, World* _world) {
	Organism* obj = new Owca(move(_position), _world);
	return obj;
}
