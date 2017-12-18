#pragma once

#include <SFML/Graphics.hpp>

struct Backgraund
{
    sf::Texture texture;
    sf::Sprite sprite;
};

void initializeBackgraund(Backgraund& backgraund);