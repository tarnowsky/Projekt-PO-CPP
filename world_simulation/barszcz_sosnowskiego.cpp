#include "barszcz_sosnowskiego.h"

using namespace std;

BarszczSosnowskiego::BarszczSosnowskiego(Point&& _position, World* _world) {
	position = _position;
	ID = 'b';
	world = _world;
	newPlantPosition = { 0, 0 };

	power = 10;
}

Organism* BarszczSosnowskiego::newObj(Point&& _position, World* _world) {
	Organism* obj = new BarszczSosnowskiego(move(_position), _world);
	return obj;
}

bool BarszczSosnowskiego::poison(Organism* _other) {
	eliminate(_other);
	eliminate(this);
	return true;
}

void BarszczSosnowskiego::action() {
	Plant::action();
	killingSpread();
}

void BarszczSosnowskiego::killingSpread() {
	int numOfChoices = 0;
	int choicesArr[4] = {};

	bool* possibleMoves = findPossibleMovementSpots();

	Organism* _other = nullptr;
	for (int direction = 0; direction < 4; direction++)
		if (possibleMoves[direction]) {
			switch (direction) {
			case UP:
				_other = world->getField({ position.x, position.y - 1 });
				if (_other && (_other->getInitiative() > 0)) eliminate(_other);
				break;
			case RIGHT:
				_other = world->getField({ position.x + 1, position.y });
				if (_other && (_other->getInitiative() > 0)) eliminate(_other);
				break;
			case DOWN:
				_other = world->getField({ position.x, position.y + 1 });
				if (_other && (_other->getInitiative() > 0)) eliminate(_other);
				break;
			case LEFT:
				_other = world->getField({ position.x - 1, position.y });
				if (_other && (_other->getInitiative() > 0)) eliminate(_other);
				break;
			}

		}
}
