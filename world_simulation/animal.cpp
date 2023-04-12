#include "animal.h"
using namespace std;

Animal::Animal(Point&& p, char _animalAscii, World* _world) {
	position.x = p.x;
	position.y = p.y;
	ID = _animalAscii;
	world = _world;
}

void Animal::action() {
	int numOfChoices = 0;
	int choicesArr[4] = {};
	bool possibleMoves[] = {true, true, true, true};
	Point prevPosition = position;

	if (position.y == 0) possibleMoves[UP] = false;
	if (position.y == world->getRows() - 1) possibleMoves[DOWN] = false;
	if (position.x == 0) possibleMoves[LEFT] = false;
	if (position.x == world->getCols() - 1) possibleMoves[RIGHT] = false;
	for (int i = 0, j = 0; i < 4; i++)
		if (possibleMoves[i]) {
			numOfChoices++;
			choicesArr[j++] = i;
		}

	int direction = choicesArr[rand() % numOfChoices];

	// check if move does collision
	Organism* _other = nullptr;
	switch (direction) {
	case UP:
		_other = world->getField({ position.x, position.y - 1 });
		if (_other) {
			if (collision(_other))
				position.y--;
		}
		else position.y--;
		break;
	case RIGHT:
		_other = world->getField({ position.x + 1, position.y });
		if (_other) {
			if (collision(_other))
				position.x++;;
		}
		else position.x++;;
		break;
	case DOWN:
		_other = world->getField({ position.x, position.y + 1 });
		if (_other) {
			if (collision(_other))
				position.y++;
		}
		else position.y++;
		break;
	case LEFT:
		_other = world->getField({ position.x - 1, position.y });
		if (_other) {
			if (collision(_other))
				position.x--;
		}
		else position.x--;
		break;
	}
	world->clearField(move(prevPosition));
	draw();
}

// return true if obj can be moved on collided tile, false otherwise
bool Animal::collision(Organism* _other) {
	if (_other->getID() == this->ID) {
		reproduce(_other);
		_other->setMakeMove(false);
		return false;
	}
	else if (power >= _other->getPower()) {
		eliminate(_other);
		return true;
	}
}

void Animal::reproduce(Organism* _other) {
	/*printf("trying to reproduct (%d, %d) + (%d, %d). Looking for place...\n",
		position.x, position.y,
		_other->getPosition().x, _other->getPosition().y);*/
	// znajdz punkt na ktorym mozna osadzic nowe zwierze
	Organism* child = nullptr;
	Point childPosition = {}, parentPosition = {};
	if (findFieldForChild(&childPosition, _other)) {
		child = new Animal(move(childPosition), ID, world);
		world->addOrganism(child);
		/*printf("reproducted (%d, %d) + (%d, %d) -> (%d, %d)\n\n",
			position.x, position.y,
			_other->getPosition().x, _other->getPosition().y,
			child->getPosition().x, child->getPosition().y);*/
	}
	//else printf("place not founded.\n\n");
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
	world->setField(this);
}

void Animal::eliminate(Organism* _other) {
	/*printf("elimination. (%d, %d) X (%d, %d)\n\n", 
		position.x, position.y,
		_other->getPosition().x, _other->getPosition().y);*/
	if (world->removeOrganism(_other));
}







