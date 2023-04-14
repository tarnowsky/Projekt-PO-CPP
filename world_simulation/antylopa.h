#pragma once
#include "animal.h"
class Antylopa :
    public Animal
{
public:
    Antylopa(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    bool menageMove(int direction) override;
    bool* findPossibleMovementSpots() override;
    bool escape() override;
    bool fight(Organism* _other) override;


};

