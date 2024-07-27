#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Food.h"



class Snake {
public:
    Snake(Grid& grid);
    void drawSnake(sf::RenderWindow& window);
    void setDirection(const sf::Vector2i& otherDirection);
    const sf::Vector2i& getDirection() const;
    void moveSnake();
    bool eatSnake(Food& food);
    std::vector<std::unique_ptr<Entity>>& getVectorSnake() ;
    void updateTextures();

private:
    void growSnake();

    Grid& grid;
    std::vector<std::unique_ptr<Entity>> snake;
    sf::Vector2i direction;
    std::vector<sf::Vector2i> previousPositions;
    sf::Vector2i globalPosition;
};