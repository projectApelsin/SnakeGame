#include "Grid.h"

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<std::shared_ptr<Entity>>(cols));
}

void Grid::initializeGrid() {
    bool isEven = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (isEven) {
                grid[i][j] = std::make_shared<Entity>(BACKGROUND_GREEN);
                grid[i][j]->setSpritePosition(sf::Vector2f(j * 50, i * 50));
            }
            else {
                grid[i][j] = std::make_shared<Entity>(BACKGROUND_LIGHT_GREEN);
                grid[i][j]->setSpritePosition(sf::Vector2f(j * 50, i * 50));
            }
            isEven = !isEven;
        }

        if (cols % 2 == 0) {
            isEven = !isEven;
        }
    }
}
void Grid::drawGrid(sf::RenderWindow& window) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            window.draw(grid[i][j]->getSprite());
        }
    }
}

const std::vector<std::vector<std::shared_ptr<Entity>>>& Grid::getGrid() const {
    return grid;
}


 