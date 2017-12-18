#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

static const sf::Color BLOCK_COLOR = sf::Color(255, 255, 0);

struct Block
{
    sf::RectangleShape shape;
    bool destroyed = false;
    bool strong = false;
};

void initializeBlocks(std::vector<Block>& blocks);
void removeDeathBlocks(std::vector<Block>& blocks);