#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Block
{
    sf::RectangleShape shape;
    bool destroyed = false;
};

void initializeBlocks(std::vector<Block>& blocks);
void removeDeathBlocks(std::vector<Block>& blocks);