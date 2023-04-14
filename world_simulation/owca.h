#pragma once
#include "animal.h"

class Owca : public Animal {
public:
	Owca(Point&& p, World* _world);
	Organism* newObj(Point&& _position, World* _world) override;
};