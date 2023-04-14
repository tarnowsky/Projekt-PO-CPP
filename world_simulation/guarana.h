#pragma once
#include "plant.h"
class Guarana :
    public Plant
{
public:
    Guarana(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    void afterDeathEffect(Organism* _other) override;

};

