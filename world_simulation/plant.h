#pragma once
#include "organism.h"
class Plant :
    public Organism
{
private:
    bool menagePlanting(int _direction);
protected:
    void addNewPlant();
public:
    Plant() = default;
    Plant(Point&& p, World* _world);
    virtual void action() override;
    bool collision(Organism* _other) override;
    void draw() override;

    virtual Organism* newObj(Point&& _position, World* _world);
    virtual bool tryingToPlant();
};

