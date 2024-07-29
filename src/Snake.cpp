#include "Snake.h"

Snake::Snake(Grid& grid_)
    : grid(grid_), direction(0, 1), globalPosition(4, 2) {
    snake.emplace_back(std::make_unique<Entity>(SNAKE_HEAD_UP));
    snake[0]->setSpritePosition(grid.getPositionByIndex(globalPosition.x, globalPosition.y));
    targetPositions.push_back(grid.getPositionByIndex(globalPosition.x, globalPosition.y));

    sf::Vector2f previousSprite = snake.back()->getSprite().getPosition();
    snake.emplace_back(std::make_unique<Entity>(SNAKE_TAIL_DOWN));
    snake.back()->setSpritePosition(sf::Vector2f(previousSprite.x, previousSprite.y + 40));
    targetPositions.push_back(sf::Vector2f(previousSprite.x, previousSprite.y + 40));

    // Initialize previous positions
    previousPositions.push_back(globalPosition);
    previousPositions.push_back(sf::Vector2i(globalPosition.x, globalPosition.y - 1));
}

std::vector<std::unique_ptr<Entity>>& Snake::getVectorSnake() {
    return snake;
}

void Snake::growSnake() {
    snake.back()->setSpriteTexture(SNAKE_BODY_VERTICAL);
    sf::Vector2f previousSnakePosition = snake.back()->getSprite().getPosition();
    snake.emplace_back(std::make_unique<Entity>(SNAKE_TAIL_DOWN));
    snake.back()->setSpritePosition(previousSnakePosition);
    previousPositions.push_back(previousPositions.back()); // Add a new position for the new segment
    targetPositions.push_back(previousSnakePosition); // добавлена новая целевая позиция
}

void Snake::drawSnake(sf::RenderWindow& window) {
    for (const auto& snakeEntity : snake) {
        window.draw(snakeEntity->getSprite());
    }
}

void Snake::setDirection(const sf::Vector2i& otherDirection) {
    // Prevent the snake from reversing
    if (direction.x != -otherDirection.x && direction.y != -otherDirection.y) {
        direction = otherDirection;
    }
}

const sf::Vector2i& Snake::getDirection() const {
    return direction;
}

bool Snake::checkSelfCollision() {
    for (std::size_t i = 1; i < previousPositions.size(); ++i) {
        if (previousPositions[0] == previousPositions[i]) {
            return true;
        }
    }
    return false;
}

bool Snake::isGameOver() const {
    return gameOver;
}

void Snake::update(float deltaTime) {
    if (gameOver) return;
    for (std::size_t i = 0; i < snake.size(); ++i) {
        sf::Vector2f currentPosition = snake[i]->getSprite().getPosition();
        sf::Vector2f targetPosition = targetPositions[i];

        sf::Vector2f direction = targetPosition - currentPosition;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 0.1f) {
            sf::Vector2f movement = direction / distance * (1000.0f * deltaTime); 
            snake[i]->updatePosition(movement);
        }
        else {
            snake[i]->setSpritePosition(targetPosition); 
        }
    }
 
}

void Snake::moveSnake() {
    if (gameOver) return;


    for (std::size_t i = snake.size() - 1; i > 0; --i) {
        previousPositions[i] = previousPositions[i - 1];
        targetPositions[i] = grid.getPositionByIndex(previousPositions[i].x, previousPositions[i].y);

    }


    globalPosition += direction;
    previousPositions[0] = globalPosition;
    targetPositions[0] = grid.getPositionByIndex(globalPosition.x, globalPosition.y);
    if (checkSelfCollision()) {
        gameOver = true;
    }
    updateTextures();
}

void Snake::updateTextures() {
    // Update the head texture based on direction
    if (direction == sf::Vector2i(0, 1)) {
        snake[0]->setSpriteTexture(SNAKE_HEAD_RIGHT);
    }
    else if (direction == sf::Vector2i(0, -1)) {
        snake[0]->setSpriteTexture(SNAKE_HEAD_LEFT);
    }
    else if (direction == sf::Vector2i(1, 0)) {
        snake[0]->setSpriteTexture(SNAKE_HEAD_DOWN);
    }
    else if (direction == sf::Vector2i(-1, 0)) {
        snake[0]->setSpriteTexture(SNAKE_HEAD_UP);
    }

    // Update the tail texture based on the second last segment's direction
    sf::Vector2i tailDirection = previousPositions[previousPositions.size() - 2] - previousPositions.back();
    if (tailDirection == sf::Vector2i(0, -1)) {
        snake.back()->setSpriteTexture(SNAKE_TAIL_RIGHT);
    }
    else if (tailDirection == sf::Vector2i(0, 1)) {
        snake.back()->setSpriteTexture(SNAKE_TAIL_LEFT);
    }
    else if (tailDirection == sf::Vector2i(-1, 0)) {
        snake.back()->setSpriteTexture(SNAKE_TAIL_DOWN);
    }
    else if (tailDirection == sf::Vector2i(1, 0)) {
        snake.back()->setSpriteTexture(SNAKE_TAIL_UP);
    }

    // Update the body textures based on segment directions
    for (int i = 1; i < snake.size() - 1; i++) {
        sf::Vector2i prevSegmentDirection = previousPositions[i - 1] - previousPositions[i];
        sf::Vector2i nextSegmentDirection = previousPositions[i] - previousPositions[i + 1];

        if (nextSegmentDirection == sf::Vector2i(1, 0) || nextSegmentDirection == sf::Vector2i(-1, 0)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_VERTICAL);
        }
        else if (nextSegmentDirection == sf::Vector2i(0, 1) || nextSegmentDirection == sf::Vector2i(0, -1)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_HORIZONTAL);
        }
        if (prevSegmentDirection == sf::Vector2i(1, 0) && nextSegmentDirection == sf::Vector2i(0, -1)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_RIGHT);
        }
        else if (prevSegmentDirection == sf::Vector2i(1, 0) && nextSegmentDirection == sf::Vector2i(0, 1)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_LEFT);
        }
        if (prevSegmentDirection == sf::Vector2i(0, 1) && nextSegmentDirection == sf::Vector2i(-1, 0)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_RIGHT);
        }
        else if (prevSegmentDirection == sf::Vector2i(0, 1) && nextSegmentDirection == sf::Vector2i(1, 0)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_RIGHT);
        }
        if (prevSegmentDirection == sf::Vector2i(-1, 0) && nextSegmentDirection == sf::Vector2i(0, -1)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_RIGHT);
        }
        else if (prevSegmentDirection == sf::Vector2i(-1, 0) && nextSegmentDirection == sf::Vector2i(0, 1)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_LEFT);
        }
        if (prevSegmentDirection == sf::Vector2i(0, -1) && nextSegmentDirection == sf::Vector2i(-1, 0)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_LEFT);
        }
        else if (prevSegmentDirection == sf::Vector2i(0, -1) && nextSegmentDirection == sf::Vector2i(1, 0)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_LEFT);
        }
    }
}

bool Snake::eatSnake(Food& food) {
    if (snake[0]->getSprite().getGlobalBounds().intersects(food.getSprite().getGlobalBounds())) {
        growSnake();
        return true;
    }
    return false;
}
