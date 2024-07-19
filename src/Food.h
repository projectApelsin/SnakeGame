#pragma once
#include "Entity.h"
#include "Const.h"
#include "random"
#include "Grid.h"

class Food : public Entity {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> distribution;
    Grid* ptrGrid;
public:
	Food(Grid& grid);
	void respawnFood();
    int test();
};