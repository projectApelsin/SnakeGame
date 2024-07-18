#include "Snake.h"

Snake::Snake() {
    snake.emplace_back(std::make_shared<Entity>(SNAKE_HEAD_UP));
    sf::Vector2f previousSprite = snake.back().get()->getSprite().getPosition();
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    snake.back().get()->setSpritePosition(sf::Vector2f(previousSprite.x, previousSprite.y + 40));
}

std::vector<std::shared_ptr<Entity>>& Snake::getVectorSnake() {
    return snake;
}

void Snake::growSnake() {
    std::shared_ptr<Entity> previousSnakeEntity = snake.back();
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    previousSnakeEntity.get()->setSpriteTexture(SNAKE_BODY_VERTICAL);
    snake.back().get()->setSpritePosition(sf::Vector2f(previousSnakeEntity.get()->getSprite().getPosition().x,
        previousSnakeEntity.get()->getSprite().getPosition().y + 40));
}

void Snake::drawSnake(sf::RenderWindow& window) {
    for (auto& snakeEntity : snake) {
        window.draw(snakeEntity.get()->getSprite());
    }
}

bool Snake::eatSnake(Food& food) {
    if (snake[0].get()->getSprite().getGlobalBounds().intersects(food.getSprite().getGlobalBounds())) {
        growSnake();
        return true;
    }
    else return false;
}