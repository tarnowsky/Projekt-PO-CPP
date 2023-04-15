#include "czlowiek.h"


using namespace std;

Czlowiek::Czlowiek(Point&& _position, World* _world) {
	position = _position;
	ID = 'C';
	world = _world;

	power = 5;
	initiative = 4;

	powerOn = false;
	powerCanBeUsed = true;
	togglePowerUsageRound = 0;
}

Organism* Czlowiek::newObj(Point&& _position, World* _world) {
	Organism* obj = new Czlowiek(move(_position), _world);
	return obj;
}

int Czlowiek::movementDirection(int* choicesArr, int n) {
	int c, ex;
	while (true) {
		c = _getch();
		if (c == 0 || c == 224) {
			ex = _getch();
			switch (ex) {
			case KEY_UP:
				for (int i = 0; i < n; i++)
					if (choicesArr[i] == UP) return UP;
				break;
			case KEY_DOWN:
				for (int i = 0; i < n; i++)
					if (choicesArr[i] == DOWN) return DOWN;
				break;
			case KEY_RIGHT:
				for (int i = 0; i < n; i++)
					if (choicesArr[i] == RIGHT) return RIGHT;
				break;
			case KEY_LEFT:
				for (int i = 0; i < n; i++)
					if (choicesArr[i] == LEFT) return LEFT;
				break;
			}
		}
		if (c == 'p' && powerCanBeUsed) {
			powerOn = true;
			togglePowerUsageRound = world->getRoundNum() + 4;
			powerCanBeUsed = false;
			killingSpread();
		}
	}
}

void Czlowiek::action() {
	if (togglePowerUsageRound == world->getRoundNum()) {
		if (powerOn) {
			powerOn = false;
			togglePowerUsageRound += 6;
		}
		else if (!powerCanBeUsed) powerCanBeUsed = true;
	}
	if (powerOn) killingSpread();
	Animal::action();
	if (powerOn) killingSpread();
}

void Czlowiek::killingSpread() {
	int numOfChoices = 0;
	int choicesArr[4] = {};

	bool* possibleMoves = findPossibleMovementSpots();

	Organism* _other = nullptr;
	for (int direction = 0; direction < 4; direction++)
		if (possibleMoves[direction]) {
			switch (direction) {
			case UP:
				_other = world->getField({ position.x, position.y - 1 });
				if (_other) eliminate(_other);
				break;
			case RIGHT:
				_other = world->getField({ position.x + 1, position.y });
				if (_other) eliminate(_other);
				break;
			case DOWN:
				_other = world->getField({ position.x, position.y + 1 });
				if (_other) eliminate(_other);
				break;
			case LEFT:
				_other = world->getField({ position.x - 1, position.y });
				if (_other) eliminate(_other);
				break;
			}
		}
}