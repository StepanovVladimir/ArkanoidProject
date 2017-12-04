#include "text.h"

void initializeText(sf::Font& font, sf::Text& text)
{
    font.loadFromFile("arialn.ttf");
    text.setFont(font);
    text.setString("You lose");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(255, 255, 255));
    text.setPosition({200, 275});
}