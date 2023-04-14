#pragma once
#include "plant.h"
class WilczeJagody :
    public Plant {
public:
    WilczeJagody(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    bool poison(Organism* _other) override;


};

