#pragma once
#include <iostream>
#include<windows.h>

#include "organism.h"

class Organism;

constexpr int SIZEOF_ORGANISM_ARR = 16;

constexpr char LEFT_TOP_CORNER = (char)218;
constexpr char RIGHT_TOP_CORNER = (char)191;
constexpr char LEFT_BOTTOM_CORNER = (char)192;
constexpr char RIGHT_BOTTOM_CORNER = (char)217;
constexpr char HORIZONTAL_LINE = (char)196;
constexpr char VERTICAL_LINE = (char)179;
constexpr char SPACE = (char)32;


struct Point {
	int x, y;
};



enum Directions {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class World {
private:
	Organism*** board;
	Organism** organismArr;
	int lenOfOrganismArr;
	int numOfOrganismsInArray;
	int rows;
	int cols;
	int roundNum;

	void prepareForNextTurn();
	void sortByInititive();
	void insertByInitiative(Organism* organism);
	void incrementMemory(int _newBlock);

public:
	World() = default;
	World(int _rows, int _cols);
	~World();

	void ShowConsoleCursor(bool showFlag);
	void nextTurn();
	void addOrganism(Organism* organism);
	bool removeOrganism(Organism* organism);

	void drawWorld();
	void drawField(Point&& p, char c);

	Organism*& getField(Point&& p);
	Organism**& getOrganismArr();
	int& getRows();
	int& getCols();
	int& getRoundNum();

	void setField(Point&& p, Organism* organism);

};