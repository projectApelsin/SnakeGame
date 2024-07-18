#include "Snake.h"

Snake::Snake() {
    // Initialize head of the snake
    snake.emplace_back(std::make_shared<Entity>(SNAKE_HEAD_UP));
    sf::Vector2f previousSpritePos = snake.back()->getSprite().getPosition();

    // Initialize tail of the snake
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    snake.back()->setSpritePosition(sf::Vector2f(previousSpritePos.x, previousSpritePos.y + 40));
}

std::vector<std::shared_ptr<Entity>>& Snake::getVectorSnake() {
    return snake;
}

void Snake::snakeGrow() {
    // Get the position of the current tail
    std::shared_ptr<Entity> previousSnakeEntity = snake.back();
    sf::Vector2f previousTailPos = previousSnakeEntity->getSprite().getPosition();

    // Update the current tail to body
    previousSnakeEntity->setSpriteTexture(SNAKE_BODY_VERTICAL);

    // Add new tail
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    snake.back()->setSpritePosition(sf::Vector2f(previousTailPos.x, previousTailPos.y + 40));
}
