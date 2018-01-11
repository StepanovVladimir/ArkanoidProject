#include "text.h"

void initializeText(String& string)
{
    string.font.loadFromFile("res/arialn.ttf");
    string.lose.setFont(string.font);
    string.lose.setString("You lose");
    string.lose.setCharacterSize(50);
    string.lose.setFillColor(sf::Color(255, 255, 255));
    string.lose.setPosition({220, 275});
    string.win.setFont(string.font);
    string.win.setString("You win");
    string.win.setCharacterSize(50);
    string.win.setFillColor(sf::Color(255, 255, 255));
    string.win.setPosition({230, 275});
}