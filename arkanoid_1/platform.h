#pragma once

#include <SFML/Graphics.hpp>

enum struct Direction
{
    NONE,
    LEFT,
    RIGHT
};

struct Platform
{
    sf::RectangleShape shape;
    Direction direction;
};

void initializePlatform(Platform& platform);
void updatePlatform(Platform& platform, float elapsedTime);
bool handlePlatformKeyPress(const sf::Event::KeyEvent& event, Platform& platform);
bool handlePlatformKeyRelease(const sf::Event::KeyEvent& event, Platform& platform);