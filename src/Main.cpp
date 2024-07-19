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
    grid.initializeGrid();
    Food food(grid);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type) {
            
            }
        }
        window.clear();
        
        grid.drawGrid(window);
        window.draw(food.getSprite());
        snake.drawSnake(window);
        window.draw(food.getSprite());

       // window.draw(entity.getSprite());
        window.display();
    }

    return 0;
}