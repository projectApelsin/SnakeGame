#include "Entity.h"

Entity::Entity(std::string& pathToTexture) {
	texture.loadFromFile(pathToTexture);
	sprite.setTexture(texture);
}