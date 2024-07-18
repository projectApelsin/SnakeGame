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
            }
            else {
                grid[i][j] = std::make_shared<Entity>(BACKGROUND_LIGHT_GREEN);
            }
            isEven = !isEven;
        }
        // Flip isEven at the end of each row to create a checkerboard pattern
        if (cols % 2 == 0) {
            isEven = !isEven;
        }
    }
}

const std::vector<std::vector<std::shared_ptr<Entity>>>& Grid::getGrid() const {
    return grid;
}