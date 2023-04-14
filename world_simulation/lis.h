#pragma once
#include "animal.h"
class Lis :
    public Animal
{
public:
    Lis(Point&& p, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    bool fight(Organism* _other) override;
};

