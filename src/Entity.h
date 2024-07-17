#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>



class Entity {
protected:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Entity(std::string& pathToTexture);
	
};