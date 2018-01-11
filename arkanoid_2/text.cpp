#include "text.h"

void initializeText(sf::Font& font, sf::Text& text)
{
    if (font.loadFromFile("res/arialn.ttf"))
    {
        text.setFont(font);
        text.setString("You lose");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(255, 255, 255));
        text.setPosition({300, 300});
        text.setOrigin({100, 25});
    }
}