#pragma once
#include "animal.h"
#include <conio.h>

constexpr int KEY_UP = 72;
constexpr int KEY_LEFT = 75;
constexpr int KEY_RIGHT = 77;
constexpr int KEY_DOWN = 80;

class Czlowiek :
    public Animal
{
public:
    int movementDirection(int* choicesArr, int n) override;
    

    Czlowiek(Point&& _position, World* _world);
    Organism* newObj(Point&& _position, World* _world) override;
    void action() override;
    void killingSpread();

};

