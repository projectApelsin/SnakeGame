#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape rect;
    sf::Texture texture;
    texture.loadFromFile("data/snake.png", sf::IntRect(sf::Vector2i(100,100), sf::Vector2i(100,100)));
    Entity entity;
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}