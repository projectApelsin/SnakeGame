#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Snake.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Online");
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromFile("data/apple.png");
    Snake snake();
  

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.display();
    }

    return 0;
}