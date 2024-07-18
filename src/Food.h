#pragma once
#include "Entity.h"
#include "Const.h"
#include "random"

class Food : public Entity {
private:
    int windowWidth;
    int windowHeight;
    int gridSize;
    std::mt19937 rng;
    std::uniform_int_distribution<int> xDistribution;
    std::uniform_int_distribution<int> yDistribution;
public:
	Food(int windowWidth, int windowHeight, int gridSize);
	void respawnFood();
};