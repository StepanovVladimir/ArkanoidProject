#pragma once

#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDTH = 600;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float PLATFORM_WIDTH = 80.f;
constexpr float PLATFORM_HEIGHT = 10.f;

enum struct DirectionPlatform
{
    NONE,
    LEFT,
    RIGHT
};

struct Platform
{
    sf::RectangleShape shape;
    DirectionPlatform direction;
};

void initializePlatform(Platform& platform);
void updatePlatform(Platform& platform, float elapsedTime);
void handlePlatformKeyPress(const sf::Event::KeyEvent& event, Platform& platform);
void handlePlatformKeyRelease(const sf::Event::KeyEvent& event, Platform& platform);