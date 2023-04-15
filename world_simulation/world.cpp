#include "organism.h"

using namespace std;

World::World(int _rows, int _cols)
	: rows(_rows), cols(_cols), organismArr(nullptr), lenOfOrganismArr(0), numOfOrganismsInArray(0), roundNum(0) {
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
	roundNum++;
	for (int i = 0; i < numOfOrganismsInArray; i++) {
		if (organismArr[i]->getMakeMove()) {
			organismArr[i]->action();
		}
	}
}

void World::prepareForNextTurn() {
	for (int i = 0; i < numOfOrganismsInArray; i++) {
		organismArr[i]->setMakeMove(true);
		organismArr[i]->incrementAge();
	}
}

void World::addOrganism(Organism* organism) {
	// zaalokuj now¹ pamiêæ jesli jest taka potrzeba
	if (numOfOrganismsInArray % SIZEOF_ORGANISM_ARR == 0) incrementMemory(SIZEOF_ORGANISM_ARR);
	// dodaj organizm
	insertByInitiative(organism);
	numOfOrganismsInArray++;
	board[organism->getPosition().y][organism->getPosition().x] = organism;
}

void World::incrementMemory(int _newBlock) {
	int prevLen = lenOfOrganismArr;
	lenOfOrganismArr = prevLen + _newBlock;
	Organism** tmp = new Organism * [lenOfOrganismArr];

	// skopiuj Organizmy ze starej tablicy do nowej
	for (int i = 0; i < prevLen; i++)
		tmp[i] = organismArr[i];

	// wyzeruj pozosta³e elementy tablicy
	for (int i = prevLen; i < lenOfOrganismArr; i++)
		tmp[i] = nullptr;

	organismArr = tmp;
	tmp = nullptr;
}

void World::sortByInititive() {
	int i, j;
	Organism* key;
	for (i = 1; i < numOfOrganismsInArray; i++) {
		key = organismArr[i];
		j = i - 1;
		while (j >= 0 && organismArr[j]->getInitiative() < key->getInitiative()) {
			organismArr[j + 1] = organismArr[j];
			j = j - 1;
		}
		organismArr[j + 1] = key;
	}
}

void World::insertByInitiative(Organism* organism) {
	// 1. znajdz pierwszy organizm z mniejsz¹ inicjatyw¹
	int indx = 0;
	for (indx; organismArr[indx] != nullptr && (organismArr[indx]->getInitiative() >= organism->getInitiative()); indx++);

	// brak oragnizmow w tabeli lub brak organizmow z mniejsz¹ inicjatyw¹
	if (!organismArr[indx]) organismArr[indx] = organism;
	else {
		// zrób mniejsce na organizm
		for (int i = numOfOrganismsInArray - 1; i >= indx; i--) organismArr[i + 1] = organismArr[i];
		// wstaw organizm na miejsce
		organismArr[indx] = organism;
	}
}


bool World::removeOrganism(Organism* organism) {
	int indx = 0;
	for (indx; indx < numOfOrganismsInArray && organismArr[indx] != organism; indx++);
	if (indx == numOfOrganismsInArray) return false;
	else for (int i = indx + 1; i < numOfOrganismsInArray; i++) organismArr[i - 1] = organismArr[i];
	organismArr[numOfOrganismsInArray - 1] = nullptr;

	board[organism->getPosition().y][organism->getPosition().x] = nullptr;
	numOfOrganismsInArray--;
}

Organism**& World::getOrganismArr() {
	return organismArr;
}

int& World::getRoundNum() {
	return roundNum;
}

Organism*& World::getField(Point&& p) {
	return board[p.y][p.x];
}

void World::setField(Point&& p, Organism* organism) {
	board[p.y][p.x] = organism;
}



void World::drawWorld() {
	system("CLS");
	/**
	aby pozbyc sie numerow:
		1. zmien -2 na -1 w forach
		2. usun 3 pierwsze linie w drugim forze
	*/
	for (int i = -1; i <= rows; i++) {
		for (int j = -1; j <= cols; j++) {
			/*if (i == -2 && (j <= -1 || j == cols) || (j == -2 && (i <= -1 || i == rows))) cout << SPACE;
			else if (i == -2) cout << (j)%10;
			else if (j == -2 && i > -1) cout << (i)%10;*/
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

void World::drawField(Point&& p, char c) {
	COORD coords = { (short)(p.x + 1), (short)(p.y + 1) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
	cout << c;
}



World::~World() {
	for (int i = 0; i < rows; i++)
		delete[] board[i];
	delete[] board;
}