#include "plant.h"
using namespace std;

Plant::Plant() 
	: newPlantPosition({ 0,0 }) {}


Plant::Plant(Point&& p, World* _world)
	: newPlantPosition({ 0,0 }) {
	position = p;
	ID = '-';
	world = _world;
}

void Plant::action() {
	if (!tryingToPlant()) return;

	int numOfChoices = 0;
	int choicesArr[4] = {};

	bool* possibleMoves = findPossibleMovementSpots();

	// prepare array to choose direction of movement from 
	for (int i = 0, j = 0; i < 4; i++)
		if (possibleMoves[i]) {
			numOfChoices++;
			choicesArr[j++] = i;
		}

	int direction = choicesArr[rand() % numOfChoices];

	if (menagePlanting(direction)) {
		addNewPlant();
		draw();
	}
}

bool Plant::tryingToPlant() {
	return (rand() % 10) < 5;
}

bool Plant::menagePlanting(int _direction) {
	bool canBePlanted = true;
	Organism* _other = nullptr;
	switch (_direction) {
	case UP:
		_other = world->getField({ position.x, position.y - 1 });
		if (_other) canBePlanted = false;
		else newPlantPosition = { position.x, position.y - 1 };
		break;
	case RIGHT:
		_other = world->getField({ position.x + 1, position.y });
		if (_other) canBePlanted = false;
		else newPlantPosition = { position.x + 1, position.y };
		break;
	case DOWN:
		_other = world->getField({ position.x, position.y + 1 });
		if (_other) canBePlanted = false;
		else newPlantPosition = { position.x, position.y + 1 };
		break;
	case LEFT:
		_other = world->getField({ position.x - 1, position.y });
		if (_other) canBePlanted = false;
		else newPlantPosition = { position.x - 1, position.y };
		break;
	}
	return canBePlanted;
}


bool Plant::collision(Organism* _other) {
	if (_other->getID() == this->ID) return false;
	else {
		if (power >= _other->getPower()) {
			Organism::eliminate(_other);
			return true;
		}
		else return false;
	}
}

void Plant::draw() {
	world->drawField(move(newPlantPosition), ID);
}

void Plant::addNewPlant() {
	Organism* child = newObj(move(newPlantPosition), world);
	child->setInitiative(initiative);
	child->setPower(power);
	world->addOrganism(child);
}

Organism* Plant::newObj(Point&& _position, World* _world) {
	Organism* obj = new Plant(move(_position), _world);
	return obj;
}

void Plant::afterDeathEffect(Organism* _other) { return; }