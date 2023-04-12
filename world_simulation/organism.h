#pragma once
#include <iostream>
#include<windows.h>


class World;
class Organism;

constexpr int SIZEOF_ORGANISM_ARR = 8;

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
	unsigned int lenOfOrganismArr;
	int numOfOrganismsInArray;
	unsigned int rows;
	unsigned int cols;
	
	int& maxInitiative();
	void prepareForNextTurn();
public:
	World() = default;
	World(unsigned int _rows, unsigned int _cols);
	~World();

	void ShowConsoleCursor(bool showFlag);
	void nextTurn();
	void drawWorld();
	void addOrganism(Organism* organism);
	void clearField(Point&& p);
	bool removeOrganism(Organism* organism);
	Organism*& getField(Point&& p);
	Organism**& getOrganismArr();
	unsigned int& getRows();
	unsigned int& getCols();

	void setField(Organism* organism);
};

class Organism {
protected:
	Point position;
	char ID;
	int power;
	int initiative;
	int age;
	bool makeMove;
	World* world;
public:
	Organism();

	char& getID();
	Point& getPosition();
	int& getPower();
	int& getInitiative();
	int& getAge();
	bool getMakeMove();


	void setPosition(Point&& p);
	void setPower(int _power);
	void setInitiative(int _initiative);
	void incrementAge();
	void setMakeMove(bool _move);


	virtual void action() abstract;
	virtual bool collision(Organism* _other) abstract;
	virtual void draw() abstract;

	~Organism() = default;
};