#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include "platform.h"
#include "blocks.h"

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
    int live;
    int score;
    bool gameOver = false;
    bool win = false;
};

void initializeBall(Ball& ball);
void updateBall(Ball& ball, float elapsedTime, Platform& platform, std::vector<Block>& blocks);