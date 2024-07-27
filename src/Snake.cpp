#include "Snake.h"

Snake::Snake(Grid& grid_)
    : grid(grid_), direction(0, 1), globalPosition(4, 2) {
    snake.emplace_back(std::make_unique<Entity>(SNAKE_HEAD_UP));
    snake[0]->setSpritePosition(grid.getGrid()[4][2]->getSprite().getPosition());
    sf::Vector2f previousSprite = snake.back()->getSprite().getPosition();
    snake.emplace_back(std::make_unique<Entity>(SNAKE_TAIL_DOWN));
    snake.back()->setSpritePosition(sf::Vector2f(previousSprite.x, previousSprite.y + 40));

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

void Snake::moveSnake() {
    // Update previous positions
    for (int i = snake.size() - 1; i > 0; --i) {
        previousPositions[i] = previousPositions[i - 1];
        snake[i]->setSpritePosition(grid.getGrid()[previousPositions[i].x][previousPositions[i].y]->getSprite().getPosition());
    }

    // Update the head position
    globalPosition += direction;
    previousPositions[0] = globalPosition;
    snake[0]->setSpritePosition(grid.getGrid()[globalPosition.x][globalPosition.y]->getSprite().getPosition());

    updateTextures();

    std::cout << snake[0]->getSprite().getPosition().x << " " << snake[0]->getSprite().getPosition().y << std::endl;
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
    for (int i = 1; i < snake.size() -1; i++) {
        sf::Vector2i prevSegmentDirection = previousPositions[i - 1] - previousPositions[i];
        sf::Vector2i nextSegmentDirection = previousPositions[i] - previousPositions[i + 1];

        if (nextSegmentDirection == sf::Vector2i(1, 0) || nextSegmentDirection == sf::Vector2i(-1, 0)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_VERTICAL);
        }
        else if (nextSegmentDirection == sf::Vector2i(0, 1) || nextSegmentDirection == sf::Vector2i(0, -1)) {
            snake[i]->setSpriteTexture(SNAKE_BODY_HORIZONTAL);
        }
        if (prevSegmentDirection == sf::Vector2i(1, 0) && nextSegmentDirection == sf::Vector2i(0, -1)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test1" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test1" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_RIGHT);
        }
        else if (prevSegmentDirection == sf::Vector2i(1, 0) && nextSegmentDirection == sf::Vector2i(0, 1)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test2" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test2" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_LEFT);
        }
        if (prevSegmentDirection == sf::Vector2i(0, 1) && nextSegmentDirection == sf::Vector2i(-1, 0)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test3" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test3" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_RIGHT);
        }
        if (prevSegmentDirection == sf::Vector2i(0, 1) && nextSegmentDirection == sf::Vector2i(1, 0)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test4" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test4" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_RIGHT);
        }
        if (prevSegmentDirection == sf::Vector2i(-1, 0) && nextSegmentDirection == sf::Vector2i(0, -1)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test5" <<std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test5" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_RIGHT);
        }
        if (prevSegmentDirection == sf::Vector2i(-1, 0) && nextSegmentDirection == sf::Vector2i(0, 1)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test6" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test6" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_TOP_LEFT);
        }
        if (prevSegmentDirection == sf::Vector2i(0, -1) && nextSegmentDirection == sf::Vector2i(-1, 0)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test7" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test7" << std::endl;
            snake[i]->setSpriteTexture(SNAKE_BODY_BOTTOM_LEFT);
        }
        if (prevSegmentDirection == sf::Vector2i(0, -1) && nextSegmentDirection == sf::Vector2i(1, 0)) {
            std::cout << prevSegmentDirection.x << " " << prevSegmentDirection.y << "test8" << std::endl;
            std::cout << nextSegmentDirection.x << " " << nextSegmentDirection.y << "test8" << std::endl;
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
