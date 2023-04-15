#include "wilcze_jagody.h"

using namespace std;

WilczeJagody::WilczeJagody(Point&& _position, World* _world) {
	position = _position;
	ID = 'j';
	world = _world;
	newPlantPosition = { 0, 0 };

	power = 99;
}

Organism* WilczeJagody::newObj(Point&& _position, World* _world) {
	Organism* obj = new WilczeJagody(move(_position), _world);
	return obj;
}

bool WilczeJagody::poison(Organism* _other) {
	world->addInfo("Eliminacja (" +
		to_string(_other->getPosition().x) + ", " + to_string(_other->getPosition().y) + ")"
	);
	world->addInfo("Eliminacja (" +
		to_string(position.x) + ", " + to_string(position.y) + ")"
	);
	eliminate(_other);
	eliminate(this);
	return true;
}
