#pragma once
#include "organism.h"
class Animal :
    public Organism
{
protected:
    bool findFieldForChild(Point* childPosition, Organism* _other);
    bool checkPottencialChildFields(bool*&& possibleDirections, Point* childPosition, Point&& parentPosition);
public:
    void eliminate(Organism* _other); 
    void reproduce(Organism* _other);

    bool collision(Organism* _other) override;
    void draw() override;
    void action() override;

    Animal(Point&& p, char _animalAscii, World* _world);
};

