#pragma once
#include "animal.h"
class Zolw :
    public Animal
{
public:
    Zolw(Point&& p, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;

    void action() override;
    bool defence(Organism* _other) override;

};

