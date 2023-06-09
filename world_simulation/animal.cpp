#include "animal.h"
using namespace std;

Animal::Animal(Point&& p, World* _world) {
	position = p;
	ID = '+';
	world = _world;
}

void Animal::action() {
	int numOfChoices = 0;
	int choicesArr[4] = {};
	Point prevPosition = position;

	bool *possibleMoves = findPossibleMovementSpots();

	// prepare array to choose direction of movement from 
	for (int i = 0, j = 0; i < 4; i++)
		if (possibleMoves[i]) {
			numOfChoices++;
			choicesArr[j++] = i;
		}

	// toss a coin for movement direction
	int direction = movementDirection(choicesArr, numOfChoices);

	if (direction == -1) return;
	// move animal to next spot
	if (menageMove(direction)) {
		clearPrevSpot(move(prevPosition));
		draw();
	}
}

int Animal::movementDirection(int* choicesArr, int numOfChoices) {
	return choicesArr[rand() % numOfChoices];
}


Organism* Animal::newObj(Point&& _position, World* _world) {
	Organism* obj = new Animal(move(_position), _world);
	return obj;
}

// return true if obj can be moved on collided tile, false otherwise
bool Animal::collision(Organism* _other) {
	if (_other->getID() == this->ID) {
		if (_other->getAge() < AGE_OF_CONSTENT) {
			return false;
		}
		reproduce(_other);
		_other->setMakeMove(false);
		return false;
	}
	else {
		return fight(_other);
	}
}

bool Animal::fight(Organism* _other) {
	if (_other->defence(this)) return false;
	if (power >= _other->getPower()) {
		if (!_other->escape()) {
			_other->afterDeathEffect(this);
			world->addInfo("Eliminacja (" +
				to_string(_other->getPosition().x) + ", " + to_string(_other->getPosition().y) + ")"
			);
			eliminate(_other);
		}
		return true;
	}
	else {
		world->addInfo("Eliminacja (" +
			to_string(position.x) + ", " + to_string(position.y) + ")"
		);
		if (_other->poison(this)) return false;
		eliminate(this);
		return false;
	}
}

bool Animal::menageMove(int direction) {
	bool canBeMoved = true;
	Organism* _other = nullptr;
	switch (direction) {
	case UP:
		_other = world->getField({ position.x, position.y - 1 });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.y--;
		}
		else position.y--;
		break;
	case RIGHT:
		_other = world->getField({ position.x + 1, position.y });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.x++;;
		}
		else position.x++;;
		break;
	case DOWN:
		_other = world->getField({ position.x, position.y + 1 });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.y++;
		}
		else position.y++;
		break;
	case LEFT:
		_other = world->getField({ position.x - 1, position.y });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.x--;
		}
		else position.x--;
		break;
	}
	return canBeMoved;
}


void Animal::reproduce(Organism* _other) {
	Organism* child = nullptr;
	Point childPosition = {}, parentPosition = {};
	if (findFieldForChild(&childPosition, _other)) {
		child = newObj(move(childPosition), world);
		child->setInitiative(initiative);
		child->setPower(power);
		world->addOrganism(child);
		child->draw();
		world->addInfo(
			"Rozmnozenie (" + to_string(position.x) + ", " + to_string(position.y) + ") + (" +
			to_string(_other->getPosition().x) + ", " + to_string(_other->getPosition().y) + ") -> (" +
			to_string(child->getPosition().x) + ", " + to_string(child->getPosition().y) + ")"
		);
	}
}

bool Animal::findFieldForChild(Point* childPosition, Organism* _other) {
	Organism* parent = nullptr;
	Point parentPosition = {};
	bool placeFounded = false;
	for (int i = 0; i < 2 && !placeFounded; i++) {
		bool possibleDirections[] = { true, true, true, true };
		if (i % 2 == 0) parent = this;
		else parent = _other;
		parentPosition = parent->getPosition();
		if (parentPosition.y == 0) possibleDirections[UP] = false;
		if (parentPosition.y == world->getRows() - 1) possibleDirections[DOWN] = false;
		if (parentPosition.x == 0) possibleDirections[LEFT] = false;
		if (parentPosition.x == world->getCols() - 1) possibleDirections[RIGHT] = false;
		placeFounded = checkPottencialChildFields(move(possibleDirections), childPosition, move(parentPosition));
	}
	if (placeFounded) return true;
	return false;
}

bool Animal::checkPottencialChildFields(bool*&& possibleDirections, Point* childPosition, Point&& parentPosition) {
	for (int i = 0; i < 4; i++) {
		if (possibleDirections[i]) {
			switch (i) {
			case UP:
				if (!world->getField({ parentPosition.x, parentPosition.y - 1 })) {
					*childPosition = { parentPosition.x, parentPosition.y - 1 };
					 return true;
				}
				break;
			case DOWN:
				if (!world->getField({ parentPosition.x, parentPosition.y + 1 })) {
					*childPosition = { parentPosition.x, parentPosition.y + 1 };
					 return true;
				}
				break;
			case RIGHT:
				if (!world->getField({ parentPosition.x + 1, parentPosition.y })) {
					*childPosition = { parentPosition.x + 1, parentPosition.y };
					 return true;
				}
				break;
			case LEFT:
				if (!world->getField({ parentPosition.x - 1, parentPosition.y })) {
					*childPosition = { parentPosition.x - 1, parentPosition.y };
					 return true;
				}
				break;
			}
		}
	}
	return false;
}


void Animal::draw() {
	world->setField(move(position), this);
	world->drawField(move(position), ID);
}


