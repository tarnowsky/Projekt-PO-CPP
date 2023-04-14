#pragma once
#include "plant.h"
class Trawa :
    public Plant {
public:
    Trawa(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
};

