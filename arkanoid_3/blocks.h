#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Block
{
    sf::RectangleShape shape;
};

void initializeBlocks(std::vector<Block>& blocks);