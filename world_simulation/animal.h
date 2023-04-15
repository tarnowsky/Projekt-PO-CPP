#pragma once
#include "organism.h"

constexpr int AGE_OF_CONSTENT = 15;

class Animal :
    public Organism
{

protected:
    bool findFieldForChild(Point* childPosition, Organism* _other);
    bool checkPottencialChildFields(bool*&& possibleDirections, Point* childPosition, Point&& parentPosition);
    virtual int movementDirection(int* choicesArr, int numOfChoices);
public:
    Animal() = default;
    void reproduce(Organism* _other);
    Animal(Point&& p, World* _world);

    virtual bool collision(Organism* _other) override;
    void draw() override;
    virtual void action() override;

    virtual bool menageMove(int _direction);
    virtual Organism* newObj(Point&& _position, World* _world);
    virtual bool fight(Organism* _other);
};

