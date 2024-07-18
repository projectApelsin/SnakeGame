#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Snake.h"
#include <vector>
#include "Grid.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Online");
    Snake snake;
    snake.snakeGrow();
    snake.snakeGrow();
    const int rows = 16;
    const int cols = 16;
    Grid grid(rows, cols);
    
    grid.initializeGrid();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        const auto& gridData = grid.getGrid();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::Sprite sprite = gridData[i][j]->getSprite();
                sprite.setPosition(j * 50, i * 50); // Adjust position based on your grid cell size
                window.draw(sprite);
            }
        }

        window.clear();
        for (auto& snakeEntity : snake.getVectorSnake()) {
            window.draw(snakeEntity.get()->getSprite());
        }

       // window.draw(entity.getSprite());
        window.display();
    }

    return 0;
}