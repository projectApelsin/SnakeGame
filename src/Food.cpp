#include "Food.h"


Food::Food(Grid& grid)
    : Entity(APPLE), rng(std::random_device{}()), distribution(0, 15) { 
    ptrGrid = &grid;
    
}

void Food::respawnFood(bool isEaten) {
    if (isEaten) {
        int x = distribution(rng);
        int y = distribution(rng);
        std::cout << x << std::endl << y << std::endl;
        std::cout << ptrGrid->getGrid()[x][y].get()->getSprite().getPosition().x << std::endl;
        setSpritePosition(ptrGrid->getGrid()[x][y].get()->getSprite().getPosition());
    }
}

