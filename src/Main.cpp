#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Snake.h"
#include <vector>
#include "Grid.h"
#include "Food.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Online");
    Snake snake;
    Grid grid(ROWS, COLUMNS);
    Food food;
    Food food1;
    food1.setSpritePosition(sf::Vector2f(0, 0));
    food.setSpritePosition(sf::Vector2f(0,0));
    grid.initializeGrid();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        const auto& gridData = grid.getGrid();
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                sf::Sprite sprite = gridData[i][j]->getSprite();
                sprite.setPosition(j * 50, i * 50); // Adjust position based on your grid cell size
                window.draw(sprite);
            }
        }
       
        window.draw(food.getSprite());
        window.draw(food1.getSprite());
        for (auto& snakeEntity : snake.getVectorSnake()) {
            if (snakeEntity && food.getSprite().getGlobalBounds().intersects(snakeEntity->getSprite().getGlobalBounds()) || snakeEntity && food1.getSprite().getGlobalBounds().intersects(snakeEntity->getSprite().getGlobalBounds())) {
                std::cout << "Food eaten!" << std::endl;
                snake.snakeGrow();
                food.setSpritePosition(sf::Vector2f(-50, -50)); // Move food offscreen temporarily
                food1.setSpritePosition(sf::Vector2f(-50, -50));
            }
            if (snakeEntity) {
                window.draw(snakeEntity->getSprite());
            }
        }

       // window.draw(entity.getSprite());
        window.display();
    }

    return 0;
}