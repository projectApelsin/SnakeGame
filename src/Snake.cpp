#include "Snake.h"

Snake::Snake(Grid& grid)
{
    ptrGrid = &grid;
    snake.emplace_back(std::make_shared<Entity>(SNAKE_HEAD_UP));
    snake[0].get()->setSpritePosition(ptrGrid->getGrid()[4][2].get()->getSprite().getPosition());
    sf::Vector2f previousSprite = snake.back().get()->getSprite().getPosition();
    snake.emplace_back(std::make_shared<Entity>(SNAKE_TAIL_DOWN));
    snake.back().get()->setSpritePosition(sf::Vector2f(previousSprite.x, previousSprite.y + 40));
    direction = sf::Vector2i(0,1);
    globalPosition = sf::Vector2i(8, 8);
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

void Snake::setDirection(const sf::Vector2i& otherDirection) {
    direction = otherDirection;
}

const sf::Vector2i& Snake::getDirection() {
    return direction;
}

void Snake::moveSnake() {
    // direction
    snake[0].get()->setSpritePosition(ptrGrid->getGrid()[globalPosition.x + direction.x][globalPosition.y + direction.y].get()->getSprite().getPosition());
    globalPosition += direction;
    sf::Vector2i previousPosition(globalPosition);
    for (int i = 1; i < snake.size(); i++) {
        snake[i].get()->setSpritePosition(sf::Vector2f(ptrGrid->getGrid()[previousPosition.x - direction.x][previousPosition.y - direction.y].get()->getSprite().getPosition().x,
            ptrGrid->getGrid()[previousPosition.x - direction.x][previousPosition.y - direction.y].get()->getSprite().getPosition().y));
        previousPosition = sf::Vector2i(previousPosition.x - direction.x, previousPosition.y - direction.y);
    }
    std::cout << snake[0].get()->getSprite().getPosition().x << " " << snake[0].get()->getSprite().getPosition().y << std::endl;
}

bool Snake::eatSnake(Food& food) {
    if (snake[0].get()->getSprite().getGlobalBounds().intersects(food.getSprite().getGlobalBounds())) {
        growSnake();
        return true;
    }
    else return false;
}