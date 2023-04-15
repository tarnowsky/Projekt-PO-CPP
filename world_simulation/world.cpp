#include "organisms.h"
#include "world.h"

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

World::World(int _rows, int _cols)
	: rows(_rows), cols(_cols), organismArr(nullptr), lenOfOrganismArr(0), numOfOrganismsInArray(0), roundNum(0), infoCount(0) {
	createBoard();
	infoRow = rows + 4;
}

void World::createBoard() {
	board = new Organism * *[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Organism * [cols];
		for (int j = 0; j < cols; j++)
			board[i][j] = nullptr;
	}
}


void World::deleteBoard() {
	for (int i = 0; i < rows; i++)
		delete[] board[i];
	delete[] board;
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

	COORD coords = { 0, (short)infoRow++ };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
	printf("Runda #%d", roundNum);

	for (int i = 0; i < numOfOrganismsInArray; i++) {
		if (organismArr[i]->getMakeMove()) {
			organismArr[i]->action();
		}
	}
	printInfo();
}

void World::printInfo() {
	COORD coords;
	for (int i = 0; i < infoCount; i++) {
		coords = { 0, (short)infoRow++ };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
		cout << i + 1 << ". " << infoBox[i];
	}
}


void World::prepareForNextTurn() {
	ShowConsoleCursor(false);
	for (int i = 0; i < numOfOrganismsInArray; i++) {
		organismArr[i]->setMakeMove(true);
		organismArr[i]->incrementAge();
	}
	infoRow = rows + 4;
}

void World::clearInfo() {
	COORD coords;
	for (short _row = rows + 2; _row <= (short)(infoRow + 2); _row++) {
		coords = { (short)(0), (short)(_row) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
		for (int i = 0; i < 70; i++) cout << SPACE;
	}
	infoCount = 0;
}
void World::addOrganism(Organism* organism) {
	// zaalokuj now¹ pamiêæ jesli jest taka potrzeba
	if (numOfOrganismsInArray % SIZEOF_ORGANISM_ARR == 0) incrementMemory(SIZEOF_ORGANISM_ARR);
	// dodaj organizm
	insertByInitiative(organism);
	numOfOrganismsInArray++;
	board[organism->getPosition().y][organism->getPosition().x] = organism;
}

void World::addInfo(string&& info) {
	if (infoCount < 15)
		infoBox[infoCount++] = info;
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

int& World::getInfoRow() {
	return infoRow;
}


Organism*& World::getField(Point&& p) {
	return board[p.y][p.x];
}

void World::setField(Point&& p, Organism* organism) {
	board[p.y][p.x] = organism;
}

void World::setInfoRow(int _num) {
	infoRow = _num;
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
	deleteBoard();
}

void World::save() {
	ofstream myFile("save.txt");

	myFile << rows << " ";
	myFile << cols << " ";
	myFile << roundNum << " ";

	myFile << infoCount << " ";

	for (int i = 0; i < infoCount; i++)
		myFile << infoBox[i] << "#";
	myFile << '\n';
	for (int i = 0; i < numOfOrganismsInArray; i++) {
		myFile << organismArr[i]->getID() << " ";
		myFile << organismArr[i]->getPosition().x << " ";
		myFile << organismArr[i]->getPosition().y << " ";
		myFile << organismArr[i]->getPower() << " ";
		myFile << organismArr[i]->getInitiative() << " ";
		myFile << organismArr[i]->getAge() << " ";
		myFile << organismArr[i]->getMakeMove() << " ";
		myFile << organismArr[i]->getPowerOn() << " ";
		myFile << organismArr[i]->getPowerCanBeUsed() << " ";
		myFile << organismArr[i]->getTogglePowerUsageRound() << " ";
		myFile << organismArr[i]->getNewPlantPosition().x << " ";
		myFile << organismArr[i]->getNewPlantPosition().y << "\n";
	}

	myFile.close();
	COORD c = { 0, rows + 2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "Stan planszy zapisany.";

}

bool World::load() {
	COORD c = { 0, rows + 2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	ifstream myFile("save.txt");
	string info;
	if (myFile.is_open()) {
		system("CLS");
		deleteBoard();

		lenOfOrganismArr = 0;
		numOfOrganismsInArray = 0;
		organismArr = nullptr;

		getline(myFile, info, SPACE);
		rows = stoi(info);

		getline(myFile, info, SPACE);
		cols = stoi(info);

		getline(myFile, info, SPACE);
		roundNum = stoi(info);

		getline(myFile, info, SPACE);
		infoCount = stoi(info);

		for (int i = 0; i < infoCount; i++) {
			getline(myFile, info, '#');
			infoBox[i] = info;
		}
		
		getline(myFile, info, '\n');

		infoRow = rows + 5;

		createBoard();

		Organism* o = nullptr;
		string organismType;

		Point position;
		while (getline(myFile, info, SPACE)) {

			organismType = info;

			getline(myFile, info, SPACE);
			position.x = stoi(info);
			getline(myFile, info, SPACE);
			position.y = stoi(info);

			if (organismType == "C") o = new Czlowiek(move(position), this);
			if (organismType == "W") o = new Wilk(move(position), this);
			if (organismType == "O") o = new Owca(move(position), this);
			if (organismType == "L") o = new Lis(move(position), this);
			if (organismType == "Z") o = new Zolw(move(position), this);
			if (organismType == "A") o = new Antylopa(move(position), this);
			if (organismType == "t") o = new Trawa(move(position), this);
			if (organismType == "m") o = new Mlecz(move(position), this);
			if (organismType == "g") o = new Guarana(move(position), this);
			if (organismType == "j") o = new WilczeJagody(move(position), this);
			if (organismType == "b") o = new BarszczSosnowskiego(move(position), this);

			getline(myFile, info, SPACE);
			o->setPower(stoi(info));

			getline(myFile, info, SPACE);
			o->setInitiative(stoi(info));

			getline(myFile, info, SPACE);
			o->setAge(stoi(info));

			getline(myFile, info, SPACE);
			o->setMakeMove(stoi(info));

			getline(myFile, info, SPACE);
			o->setPowerOn(stoi(info));

			getline(myFile, info, SPACE);
			o->setPowerCanBeUsed(stoi(info));

			getline(myFile, info, SPACE);
			o->setTogglePowerUsageRound(stoi(info));
			
			getline(myFile, info, SPACE);
			position.x = stoi(info);
			getline(myFile, info, '\n');
			position.y = stoi(info);

			o->setNewPlantPosition(move(position));

			addOrganism(o);
		}

		drawWorld();

		myFile.close();

		c = { 0, (short)(rows + 2)};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		cout << "Zapis wczytany";

		c = { 0, (short)(rows + 4) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		printf("Runda #%d", roundNum);
		return true;
	}
	

	else cout << "Plik zapisu nieznaleziony";
	return false;
}