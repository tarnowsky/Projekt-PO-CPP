#include "plant.h"
using namespace std;

Plant::Plant(Point&& p, World* _world) {
	position = p;
	ID = 'P';
	world = _world;
	makeMove = false;
	age = 0;
	initiative = 0;
	power = 0;
	newPlantPosition = { 0, 0 };
}

void Plant::action() {
	if ((rand() % 10) >= 5) return;

	int numOfChoices = 0;
	int choicesArr[4] = {};
	bool possiblePlantSpots[] = { true, true, true, true };

	if (position.y == 0) possiblePlantSpots[UP] = false;
	if (position.y == world->getRows() - 1) possiblePlantSpots[DOWN] = false;
	if (position.x == 0) possiblePlantSpots[LEFT] = false;
	if (position.x == world->getCols() - 1) possiblePlantSpots[RIGHT] = false;
	for (int i = 0, j = 0; i < 4; i++)
		if (possiblePlantSpots[i]) {
			numOfChoices++;
			choicesArr[j++] = i;
		}
	int direction = choicesArr[rand() % numOfChoices];

	// check if move does collision
	bool canBePlanted = true;

	Organism* _other = nullptr;
	switch (direction) {
	case UP:
		_other = world->getField({ position.x, position.y - 1 });
		if (_other) {
			canBePlanted = collision(_other);
			if (canBePlanted)
				newPlantPosition = { position.x, position.y - 1 };
		}
		else newPlantPosition = { position.x, position.y - 1 };
		break;
	case RIGHT:
		_other = world->getField({ position.x + 1, position.y });
		if (_other) {
			canBePlanted = collision(_other);
			if (canBePlanted)
				newPlantPosition = { position.x + 1, position.y };
		}
		else newPlantPosition = { position.x + 1, position.y };
		break;
	case DOWN:
		_other = world->getField({ position.x, position.y + 1 });
		if (_other) {
			canBePlanted = collision(_other);
			if (canBePlanted)
				newPlantPosition = { position.x, position.y + 1 };
		}
		else newPlantPosition = { position.x, position.y + 1 };
		break;
	case LEFT:
		_other = world->getField({ position.x - 1, position.y });
		if (_other) {
			canBePlanted = collision(_other);
			if (canBePlanted)
				newPlantPosition = { position.x - 1, position.y };
		}
		else newPlantPosition = { position.x - 1, position.y };
		break;
	}
	if (canBePlanted) {
		addNewPlant();
		draw();
	}
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