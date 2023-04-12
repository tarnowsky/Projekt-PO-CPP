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