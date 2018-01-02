#include "platform.h"

constexpr float PLATFORM_SPEED = 450;
const sf::Color PLATFORM_COLOR = sf::Color(255, 0, 0);
static const sf::Vector2f PLATFORM_INITIAL_POSITION = {300, 575};

void initializePlatform(Platform& platform)
{
    platform.direction = DirectionPlatform::NONE;
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
    case DirectionPlatform::LEFT:
        if (platform.shape.getPosition().x > platform.shape.getOrigin().x)
        {
            position.x -= step;
        }
        break;
    case DirectionPlatform::RIGHT:
        if (platform.shape.getPosition().x < WINDOW_WIDTH - platform.shape.getOrigin().x)
        {
            position.x += step;
        }
        break;
    case DirectionPlatform::NONE:
        break;
    }
    platform.shape.setPosition(position);
}

void handlePlatformKeyPress(const sf::Event::KeyEvent& event, Platform& platform)
{
    switch (event.code)
    {
    case sf::Keyboard::Left:
        platform.direction = DirectionPlatform::LEFT;
        break;
    case sf::Keyboard::Right:
        platform.direction = DirectionPlatform::RIGHT;
        break;
    }
}

void handlePlatformKeyRelease(const sf::Event::KeyEvent& event, Platform& platform)
{
    switch (event.code)
    {
    case sf::Keyboard::Left:
        if (platform.direction == DirectionPlatform::LEFT)
        {
            platform.direction = DirectionPlatform::NONE;
        }
        break;
    case sf::Keyboard::Right:
        if (platform.direction == DirectionPlatform::RIGHT)
        {
            platform.direction = DirectionPlatform::NONE;
        }
        break;
    }
}