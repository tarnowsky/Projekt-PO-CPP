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

	bool powerOn;
	bool powerCanBeUsed;
	int togglePowerUsageRound;

	Point newPlantPosition;

	World* world;
public:
	Organism();

	char& getID();
	Point& getPosition();
	int& getPower();
	int& getInitiative();
	int& getAge();
	bool getMakeMove();
	bool getPowerOn();
	bool getPowerCanBeUsed();
	int getTogglePowerUsageRound();
	Point& getNewPlantPosition();

	void setPosition(Point&& _position);
	void setPower(int _power);
	void setInitiative(int _initiative);
	void setMakeMove(bool _move);
	void setPowerOn(bool _on);
	void setPowerCanBeUsed(bool _canBeUsed);
	void setTogglePowerUsageRound(int _round);
	void setNewPlantPosition(Point&& _position);
	void setAge(int _age);

	void incrementAge();
	void clearPrevSpot(Point&& _prevPosition);
	void eliminate(Organism* _other);

	virtual bool defence(Organism* _other);
	virtual bool escape();
	virtual bool* findPossibleMovementSpots();
	virtual void afterDeathEffect(Organism* _other);
	virtual bool poison(Organism* _other);

	virtual void action() abstract;
	virtual bool collision(Organism* _other) abstract;
	virtual void draw() abstract;
};