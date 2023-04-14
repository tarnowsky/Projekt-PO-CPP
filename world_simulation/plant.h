#pragma once
#include "organism.h"
class Plant :
    public Organism
{
private:
    bool menagePlanting(int _direction);
protected:
    Point newPlantPosition;
    void addNewPlant();
public:
    Plant();
    Plant(Point&& p, World* _world);
    void action() override;
    bool collision(Organism* _other) override;
    void draw() override;

    virtual Organism* newObj(Point&& _position, World* _world);
    virtual bool tryingToPlant();
    virtual void afterDeathEffect(Organism* _other) override;

};

