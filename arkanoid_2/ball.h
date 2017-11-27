#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "platform.h"

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

void initializeBall(Ball& ball);
void updateBall(Ball& ball, float elapsedTime, Platform& platform);