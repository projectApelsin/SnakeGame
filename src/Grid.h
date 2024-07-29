#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Entity.h"



class Grid {
public:
    Grid(int rows, int cols);
    void initializeGrid();
    const std::vector<std::vector<std::shared_ptr<Entity>>>& getGrid() const;
    void drawGrid(sf::RenderWindow& window);
    const sf::Vector2f getStartPosition() const;
    const sf::Vector2f getPositionByIndex(int x, int y) const;
    

private:
    int rows;
    int cols;
    std::vector<std::vector<std::shared_ptr<Entity>>> grid;
};;