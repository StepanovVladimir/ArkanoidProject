#pragma once

#include <SFML/Graphics.hpp>

struct String
{
    sf::Font font;
    sf::Text lose;
    sf::Text win;
};

void initializeText(String& string);