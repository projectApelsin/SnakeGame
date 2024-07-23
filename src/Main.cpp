#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Snake.h"
#include <vector>
#include "Grid.h"
#include "Food.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Snake Online");
    Grid grid(ROWS, COLUMNS);
    grid.initializeGrid();
    Snake snake(grid);
    Food food(grid);
    sf::Clock clock;
    sf::Sprite sprite;
    snake.growSnake();
    snake.growSnake();
    const sf::Time timePerFrame = sf::seconds(0.5f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle user input for snake direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (snake.getDirection().x == 0) {
                snake.setDirection(sf::Vector2i(-1, 0));

            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (snake.getDirection().x == 0) {
                snake.setDirection(sf::Vector2i(1, 0));

            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (snake.getDirection().y == 0) {
                snake.setDirection(sf::Vector2i(0, -1));

            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (snake.getDirection().y == 0) {
                snake.setDirection(sf::Vector2i(0, 1));

            }
        }

        if (clock.getElapsedTime() >= timePerFrame) {
            snake.moveSnake();
            clock.restart();
        }

        food.respawnFood(snake.eatSnake(food));

        window.clear();
        grid.drawGrid(window);
        window.draw(food.getSprite());
        snake.drawSnake(window);
        window.draw(food.getSprite());
        window.display();
    }

    return 0;
}