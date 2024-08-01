#include "Entity.h"

Entity::Entity(const char* pathToTexture)
{
	texture.loadFromFile(pathToTexture);
	sprite.setTexture(texture);
}

const sf::Sprite& Entity::getSprite() const{
	return sprite;
}

void Entity::setSpritePosition(const sf::Vector2f& position) {
	sprite.setPosition(position);
}

void Entity::setSpriteTexture(const char* pathToTexture) {
	texture.loadFromFile(pathToTexture);
}

void Entity::updatePosition(const sf::Vector2f& otherPosition) {
	sprite.setPosition(sprite.getPosition().x + otherPosition.x, sprite.getPosition().y + otherPosition.y);
}
