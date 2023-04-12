#pragma once
#include "world.h"


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
	void eliminate(Organism* _other);

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