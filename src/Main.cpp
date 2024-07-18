#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Snake.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Online");
    Snake snake;
    snake.snakeGrow();
    snake.snakeGrow();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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