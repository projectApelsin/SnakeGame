#include "Food.h"


Food::Food(Grid& grid_)
    : Entity(APPLE), rng(std::random_device{}()), distribution(0, ROWS - 1),grid(grid_) {
    respawnFood(true);
}

void Food::respawnFood(bool isEaten) {
    if (isEaten) {
        int x = distribution(rng);
        int y = distribution(rng);
        std::cout << x << std::endl << y << std::endl;
        std::cout << grid.getGrid()[x][y]->getSprite().getPosition().x << std::endl;
        setSpritePosition(grid.getGrid()[x][y]->getSprite().getPosition());
    }
}

