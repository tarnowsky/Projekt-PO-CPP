#include "organism.h"

using namespace std;

World::World(unsigned int _rows, unsigned int _cols)
	: rows(_rows), cols(_cols), organismArr(nullptr), lenOfOrganismArr(0), numOfOrganismsInArray(0) {
	board = new Organism ** [rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Organism*[cols];
		for (int j = 0; j < cols; j++)
			board[i][j] = nullptr;
	}
}

unsigned int& World::getRows() {
	return rows;
}

unsigned int& World::getCols() {
	return cols;
}

void World::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void World::nextTurn() {
	prepareForNextTurn();
	//printf("Organisms on board -> %d\n", lenOfOrganismArr);
	for (int movesMade = 0; movesMade < numOfOrganismsInArray;) {
		int currInitiative = maxInitiative();
		if (currInitiative == -1) break;
		for (int j = 0, counter = 0; counter < numOfOrganismsInArray && j < lenOfOrganismArr; j++) {
			if (organismArr[j]) {
				if (organismArr[j]->getInitiative() == currInitiative) {
					if (organismArr[j]->getMakeMove()) {
						//printf("Action made by (%d, %d)\n", organismArr[j]->getPosition().x, organismArr[j]->getPosition().y);
						organismArr[j]->action();
						// po akcji mo¿e ju¿ nie istnieæ
						if (organismArr[j]) organismArr[j]->setMakeMove(false);
						movesMade++;
					}
					//else printf("Action has not been made by (%d, %d)\n", organismArr[j]->getPosition().x, organismArr[j]->getPosition().y);
				}
				counter++;
			}
		}
	}
}

void World::prepareForNextTurn() {
	int j = 0;
	for (int i = 0; j < numOfOrganismsInArray && i < lenOfOrganismArr; i++) {
		if (organismArr[i] != nullptr) {
			organismArr[i]->setMakeMove(true);
			organismArr[i]->incrementAge();
			j++;
		}
	}
}

int& World::maxInitiative() {
	int currInitiative = -1;
	for (int i = 0, j = 0; j < numOfOrganismsInArray && i < lenOfOrganismArr; i++) {
		if (organismArr[i]) {
			if (organismArr[i]->getMakeMove())
				if (organismArr[i]->getInitiative() > currInitiative)
					currInitiative = organismArr[i]->getInitiative();
			j++;
		}
	}
	return currInitiative;
}


void World::addOrganism(Organism* organism) {
	if (numOfOrganismsInArray % SIZEOF_ORGANISM_ARR == 0) {
		int prevLen = lenOfOrganismArr;
		lenOfOrganismArr = SIZEOF_ORGANISM_ARR + prevLen;
		Organism** tmp = new Organism * [lenOfOrganismArr];

		for (int i = 0; i < lenOfOrganismArr; i++) {
			if (prevLen == 0 || i >= prevLen) tmp[i] = nullptr;
			else tmp[i] = organismArr[i];
		}
		tmp[prevLen] = organism;

		organismArr = tmp;
		tmp = nullptr;
	}
	else {
		for (int i = 0; i <= numOfOrganismsInArray; i++) {
			if (organismArr[i] == nullptr) {
				organismArr[i] = organism;
				break;
			}
		}
	}
	numOfOrganismsInArray++;
	board[organism->getPosition().y][organism->getPosition().x] = organism;
}

bool World::removeOrganism(Organism* organism) {
	for (int i = 0, j = 0; j < numOfOrganismsInArray && i < lenOfOrganismArr; i++) {
		if (organismArr[i]) {
			j++;
			if (organismArr[i] == organism) {
				organismArr[i] = nullptr;
				numOfOrganismsInArray--;
				return true;
			}
		}
	}
	return false;
}

Organism**& World::getOrganismArr() {
	return organismArr;
}


Organism*& World::getField(Point&& p) {
	return board[p.y][p.x];
}

void World::setField(Organism* organism) {
	board[organism->getPosition().y][organism->getPosition().x] = organism;
}


void World::drawWorld() {
	system("CLS");
	for (int i = -1; i <= (int)rows; i++) {
		for (int j = -1; j <= (int)cols; j++) {
			if (i == -1 && j == -1) cout << LEFT_TOP_CORNER;
			else if (i == -1 && j == cols) cout << RIGHT_TOP_CORNER;
			else if (i == rows && j == -1) cout << LEFT_BOTTOM_CORNER;
			else if (i == rows && j == cols) cout << RIGHT_BOTTOM_CORNER;
			else if (i == -1 || i == rows) cout << HORIZONTAL_LINE;
			else if (j == -1 || j == cols) cout << VERTICAL_LINE;
			else if (board[i][j]) cout << board[i][j]->getID();
			else cout << SPACE;
		}
		cout << endl;
	}
}

void World::clearField(Point&& p) {
	board[p.y][p.x] = nullptr;
}



World::~World() {
	for (int i = 0; i < rows; i++)
		delete[] board[i];
	delete[] board;
}

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