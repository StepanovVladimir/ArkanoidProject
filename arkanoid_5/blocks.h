#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

static const sf::Color BLOCK_COLOR = sf::Color(255, 255, 0);
static const sf::Color BONUS_LIVE_COLOR = sf::Color(255, 0, 0);
static const sf::Color BONUS_EXTENSION_COLOR = sf::Color(0, 255, 255);
static const sf::Color BONUS_SLOWING_COLOR = sf::Color(255, 0, 255);

enum struct DirectionBlocks
{
    NONE,
    STRONG,
    BONUS_LIVE,
    BONUS_EXTENSION,
    BONUS_SLOWING
};

struct Block
{
    sf::RectangleShape shape;
    bool destroyed;
    DirectionBlocks direction;
};

void initializeBlocks(std::vector<Block>& blocks);
void removeDeathBlocks(std::vector<Block>& blocks);