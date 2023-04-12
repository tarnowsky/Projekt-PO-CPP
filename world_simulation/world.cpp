#include "organism.h"

using namespace std;

World::World(int _rows, int _cols)
	: rows(_rows), cols(_cols), organismArr(nullptr), lenOfOrganismArr(0), numOfOrganismsInArray(0) {
	board = new Organism * *[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Organism * [cols];
		for (int j = 0; j < cols; j++)
			board[i][j] = nullptr;
	}
}

int& World::getRows() {
	return rows;
}

int& World::getCols() {
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
	/**
	aby pozbyc sie numerow:
		1. zmien -2 na -1 w forach
		2. usun 3 pierwsze linie w drugim forze
	*/
	for (int i = -2; i <= rows; i++) {
		for (int j = -2; j <= cols; j++) {
			if (i == -2 && (j <= -1 || j == cols) || (j == -2 && (i <= -1 || i == rows))) cout << SPACE;
			else if (i == -2) cout << (j)%10;
			else if (j == -2 && i > -1) cout << (i)%10;
			else if (i == -1 && j == -1) cout << LEFT_TOP_CORNER;
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