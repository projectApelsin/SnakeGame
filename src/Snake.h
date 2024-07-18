#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Food.h"

class Snake {
public:
    Snake();
    std::vector<std::shared_ptr<Entity>>& getVectorSnake();
    void growSnake();
    void drawSnake(sf::RenderWindow& window);

    bool eatSnake(Food& food);

private:
    std::vector<std::shared_ptr<Entity>> snake;
};