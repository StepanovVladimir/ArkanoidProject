#include "platform.h"

constexpr float PLATFORM_SPEED = 425.f;
constexpr float PLATFORM_WIDTH = 100.f;
constexpr float PLATFORM_HEIGHT = 10.f;
const sf::Color PLATFORM_COLOR = sf::Color(255, 0, 0);
static const sf::Vector2f PLATFORM_INITIAL_POSITION = {300, 575};

void initializePlatform(Platform& platform)
{
    platform.direction = Direction::NONE;
    platform.shape.setSize({PLATFORM_WIDTH, PLATFORM_HEIGHT});
    platform.shape.setOrigin({PLATFORM_WIDTH / 2, 0});
    platform.shape.setFillColor(PLATFORM_COLOR);
    platform.shape.setPosition(PLATFORM_INITIAL_POSITION);
    platform.shape.setOutlineColor(sf::Color(0, 0, 0));
    platform.shape.setOutlineThickness(1.5);
}

void updatePlatform(Platform& platform, float elapsedTime)
{
    const float step = PLATFORM_SPEED * elapsedTime;
    sf::Vector2f position = platform.shape.getPosition();
    switch (platform.direction)
    {
    case Direction::LEFT:
        if (platform.shape.getPosition().x > PLATFORM_WIDTH / 2)
        {
            position.x -= step;
        }
        break;
    case Direction::RIGHT:
        if (platform.shape.getPosition().x < WINDOW_WIDTH - PLATFORM_WIDTH / 2)
        {
            position.x += step;
        }
        break;
    case Direction::NONE:
        break;
    }
    platform.shape.setPosition(position);
}

void handlePlatformKeyPress(const sf::Event::KeyEvent& event, Platform& platform)
{
    switch (event.code)
    {
    case sf::Keyboard::Left:
        platform.direction = Direction::LEFT;
        break;
    case sf::Keyboard::Right:
        platform.direction = Direction::RIGHT;
        break;
    }
}

void handlePlatformKeyRelease(const sf::Event::KeyEvent& event, Platform& platform)
{
    switch (event.code)
    {
    case sf::Keyboard::Left:
        if (platform.direction == Direction::LEFT)
        {
            platform.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::Right:
        if (platform.direction == Direction::RIGHT)
        {
            platform.direction = Direction::NONE;
        }
        break;
    }
}