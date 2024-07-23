#include "Snake.h"

Snake::Snake(Grid& grid)
    : ptrGrid(&grid), direction(0, 1), globalPosition(4, 2) {
    snake.emplace_back(std::make_shared<Entity>(SNAKE_HEAD_UP));
    snake[0]->setSpritePosition(ptrGrid->getGrid()[4][2]->getSprite().getPosition());
    sf::Vector2f previousSprite = snake.back()->getSprite().getPosition();
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    snake.back()->setSpritePosition(sf::Vector2f(previousSprite.x, previousSprite.y + 40));

    // Initialize previous positions
    previousPositions.push_back(globalPosition);
    previousPositions.push_back(sf::Vector2i(globalPosition.x, globalPosition.y - 1));
}

std::vector<std::shared_ptr<Entity>>& Snake::getVectorSnake() {
    return snake;
}

void Snake::growSnake() {
    std::shared_ptr<Entity> previousSnakeEntity = snake.back();
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    previousSnakeEntity->setSpriteTexture(SNAKE_BODY_VERTICAL);
    snake.back()->setSpritePosition(previousSnakeEntity->getSprite().getPosition());
    previousPositions.push_back(previousPositions.back()); // Add a new position for the new segment
}

void Snake::drawSnake(sf::RenderWindow& window) {
    for (auto& snakeEntity : snake) {
        window.draw(snakeEntity->getSprite());
    }
}

void Snake::setDirection(const sf::Vector2i& otherDirection) {
    // Prevent the snake from reversing
    if (direction.x != -otherDirection.x && direction.y != -otherDirection.y) {
        direction = otherDirection;
    }
}

const sf::Vector2i& Snake::getDirection() {
    return direction;
}

void Snake::moveSnake() {
    // Update previous positions
    for (int i = snake.size() - 1; i > 0; --i) {
        previousPositions[i] = previousPositions[i - 1];
        snake[i]->setSpritePosition(ptrGrid->getGrid()[previousPositions[i].x][previousPositions[i].y]->getSprite().getPosition());
    }

    // Update the head position
    globalPosition += direction;
    previousPositions[0] = globalPosition;
    snake[0]->setSpritePosition(ptrGrid->getGrid()[globalPosition.x][globalPosition.y]->getSprite().getPosition());

    std::cout << snake[0]->getSprite().getPosition().x << " " << snake[0]->getSprite().getPosition().y << std::endl;
}

bool Snake::eatSnake(Food& food) {
    if (snake[0]->getSprite().getGlobalBounds().intersects(food.getSprite().getGlobalBounds())) {
        growSnake();
        return true;
    }
    return false;
}
