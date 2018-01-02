#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.h"

enum struct DirectionBonuses
{
    LIVE,
    EXTENSION,
    SLOWING
};

struct Bonus
{
    sf::CircleShape shape;
    bool destroyed = false;
    DirectionBonuses direction;
};

void initializeBonus(std::vector<Bonus>& bonuses, Block& block);
void updateBonuses(std::vector<Bonus>& bonuses, float elapsedTime, Platform& platform, Ball& ball);
void removeDeathBonuses(std::vector<Bonus>& bonuses);