#include "organism.h"

using namespace std;

Organism::Organism() {
	position = { 0,0 };
	ID = NULL;
	power = NULL;
	initiative = 0;
	age = 0;
	world = nullptr;
	makeMove = false;
}

void Organism::eliminate(Organism* _other) {
	world->drawField(move(_other->getPosition()), SPACE);
	world->removeOrganism(_other);
}

bool Organism::defence(Organism* _other) {
	return false;
}

bool Organism::escape() {
	return false;
}

void Organism::clearPrevSpot(Point&& prevPosition) {
	world->setField(move(prevPosition), nullptr);
	world->drawField(move(prevPosition), SPACE);
}

bool* Organism::findPossibleMovementSpots() {
	bool possibleMoves[] = { true, true, true, true };

	if (position.y == 0) possibleMoves[UP] = false;
	if (position.y == world->getRows() - 1) possibleMoves[DOWN] = false;
	if (position.x == 0) possibleMoves[LEFT] = false;
	if (position.x == world->getCols() - 1) possibleMoves[RIGHT] = false;

	return possibleMoves;
}

void Organism::afterDeathEffect(Organism* _other) { return; }

// ORGANISM GETTERS
char& Organism::getID() {
	return ID;
}

Point& Organism::getPosition() {
	return position;
}

int& Organism::getPower() {
	return power;
}

int& Organism::getInitiative() {
	return initiative;
}

int& Organism::getAge() {
	return age;
}

bool Organism::getMakeMove() {
	return makeMove;
}


// ORGANISM SETTERS

void Organism::setPosition(Point&& p) {
	position.x = p.x + 1;
	position.y = p.y + 1;
}

void Organism::setPower(int _power) {
	power = _power;
}

void Organism::setInitiative(int _initiative) {
	initiative = _initiative;
}

void Organism::incrementAge() {
	age++;
}

void Organism::setMakeMove(bool _move) {
	makeMove = _move;
}