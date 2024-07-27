#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Const.h"



class Entity {
private:
	sf::Sprite sprite;
	sf::Texture texture;;

public:
	Entity(const char* pathToTexture);

	const sf::Sprite& getSprite() const;
	void setSpritePosition(const sf::Vector2f& position);
	void setSpriteTexture(const char* pathToTexture);
};