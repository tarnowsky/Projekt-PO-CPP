#pragma once
#include "organism.h"
class Plant :
    public Organism
{
protected:
    Point newPlantPosition;
    void addNewPlant();
public:
    Plant(Point&& p, World* _world);
    void action() override;
    bool collision(Organism* _other) override;
    void draw() override;

    virtual Organism* newObj(Point&& _position, World* _world);

};

