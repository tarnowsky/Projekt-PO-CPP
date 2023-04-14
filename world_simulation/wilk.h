#pragma once
#include "animal.h"

class Wilk :
    public Animal {
public:
    Wilk(Point&& p, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;

};

