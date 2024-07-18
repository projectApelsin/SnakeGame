#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

class Snake {
public:
    Snake();
    std::vector<std::shared_ptr<Entity>>& getVectorSnake();
    void snakeGrow();

private:
    std::vector<std::shared_ptr<Entity>> snake;
};