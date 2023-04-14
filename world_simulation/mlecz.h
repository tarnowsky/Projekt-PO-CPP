#pragma once
#include "plant.h"
class Mlecz :
    public Plant {
public:
    Mlecz(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    bool tryingToPlant() override;
};

