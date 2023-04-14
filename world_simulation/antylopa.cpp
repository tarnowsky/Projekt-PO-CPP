#include "antylopa.h"
using namespace std;

Antylopa::Antylopa(Point&& _position, World* _world) {
	position = _position;
	world = _world;
	power = 4;
	initiative = 4;
	ID = 'A';
}

Organism* Antylopa::newObj(Point&& _position, World* _world) {
	Organism* obj = new Antylopa(move(_position), _world);
	return obj;
}

bool* Antylopa::findPossibleMovementSpots() {
	bool possibleMoves[] = { true, true, true, true };

	if (position.y < 2) possibleMoves[UP] = false;
	if (position.y >= world->getRows() - 2) possibleMoves[DOWN] = false;
	if (position.x < 2) possibleMoves[LEFT] = false;
	if (position.x >= world->getCols() - 2) possibleMoves[RIGHT] = false;

	return possibleMoves;
}

bool Antylopa::menageMove(int direction) {
	bool canBeMoved = true;
	Organism* _other = nullptr;
	switch (direction) {
	case UP:
		_other = world->getField({ position.x, position.y - 2 });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.y -= 2;
		}
		else position.y -= 2;
		break;
	case RIGHT:
		_other = world->getField({ position.x + 2, position.y });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.x += 2;
		}
		else position.x += 2;
		break;
	case DOWN:
		_other = world->getField({ position.x, position.y + 2 });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.y += 2;
		}
		else position.y += 2;
		break;
	case LEFT:
		_other = world->getField({ position.x - 2, position.y });
		if (_other) {
			canBeMoved = collision(_other);
			if (canBeMoved)
				position.x -= 2;
		}
		else position.x -= 2;
		break;
	}
	return canBeMoved;
}

bool Antylopa::escape() {
	if (rand() % 10 < 5) return false;

	int numOfChoices = NULL;
	int choicesArr[4] = {};
	Point prevPosition = position;
	bool freeSpotFounded = NULL;
	int direction = NULL;

	bool* possibleMoves = findPossibleMovementSpots();

	// prepare array to choose direction of movement from 
	for (int i = 0, j = 0; i < 4; i++)
		if (possibleMoves[i]) {
			numOfChoices++;
			choicesArr[j++] = i;
		}

	Organism* _other = nullptr;
	for (int i = 0; i < numOfChoices; i++) {
		direction = choicesArr[i];
		freeSpotFounded = true;

		switch (direction) {
		case UP:
			_other = world->getField({ position.x, position.y - 1 });
			if (_other) {
				freeSpotFounded = false;
				break;
			}
			else position.y--;
			break;
		case RIGHT:
			_other = world->getField({ position.x + 1, position.y });
			if (_other) {
				freeSpotFounded = false;
				break;
			}
			else position.x++;;
			break;
		case DOWN:
			_other = world->getField({ position.x, position.y + 1 });
			if (_other) {
				freeSpotFounded = false;
				break;
			}
			else position.y++;
			break;
		case LEFT:
			_other = world->getField({ position.x - 1, position.y });
			if (_other) {
				freeSpotFounded = false;
				break;
			}
			else position.x--;
			break;
		}
		if (freeSpotFounded) break;
	}
	
	if (freeSpotFounded) {
		clearPrevSpot(move(prevPosition));
		draw();
	}

	return true;
}

bool Antylopa::fight(Organism* _other) {
	if (_other->defence(this)) return false;
	if (power >= _other->getPower()) {
		if (!_other->escape()) {
			_other->afterDeathEffect(this);
			Organism::eliminate(_other);
		}
		return true;
	}
	else {
		if (_other->poison(this)) return false;
		if (!escape())
			Organism::eliminate(this);
		return false;
	}
}
