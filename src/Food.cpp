#include "Food.h"



Food::Food(int windowWidth, int windowHeight, int gridSize)
    : Entity(APPLE), windowWidth(windowWidth), windowHeight(windowHeight), gridSize(gridSize),
    rng(std::random_device{}()),
    xDistribution(0, (windowWidth / gridSize) - 1), yDistribution(0, (windowHeight / gridSize) - 1) {
    respawnFood();
}

void Food::respawnFood() {
    int x = xDistribution(rng);
    int y = yDistribution(rng);
    setSpritePosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
   
}