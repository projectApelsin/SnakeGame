#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Food.h"

class Snake {
public:
    Snake(Grid& grid);
    std::vector<std::shared_ptr<Entity>>& getVectorSnake();
    void growSnake();
    void drawSnake(sf::RenderWindow& window);
    void moveSnake();
    bool eatSnake(Food& food);
    void setDirection(const sf::Vector2i& otherDirection);
    const sf::Vector2i& getDirection();
    void updateTextures();

private:
    std::vector<std::shared_ptr<Entity>> snake;
    Grid* ptrGrid;
    sf::Vector2i globalPosition;
    sf::Vector2i direction;
    std::vector<sf::Vector2i> previousPositions;
};