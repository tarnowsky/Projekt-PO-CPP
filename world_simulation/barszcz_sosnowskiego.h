#pragma once
#include "plant.h"
class BarszczSosnowskiego :
    public Plant
{
private:
    void killingSpread();
public:
    BarszczSosnowskiego(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    bool poison(Organism* _other) override;
    void action() override;

};

