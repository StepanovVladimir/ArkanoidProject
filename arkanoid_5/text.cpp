#include "text.h"

void initializeText(sf::Font& font, sf::Text (&texts)[TEXT_COUNT])
{
    font.loadFromFile("arialn.ttf");
    for (auto& text : texts)
    {
        text.setFont(font);
        text.setFillColor(sf::Color(255, 255, 255));
        text.setOutlineColor(sf::Color(0, 0, 0));
        text.setOutlineThickness(1.5);
    }
    texts[HOME].setCharacterSize(50);
    texts[HOME].setPosition({120, 50});
    texts[HOME].setString("      ARKANOID\n\n\n\nPress Enter to start");
    texts[LOSE].setCharacterSize(50);
    texts[LOSE].setPosition({100, 265});
    texts[LOSE].setString("          You lose\nPress Enter to restart");
    texts[WIN].setCharacterSize(50);
    texts[WIN].setPosition({100, 265});
    texts[WIN].setString("           You win\nPress Enter to restart");
    texts[PAUSE].setCharacterSize(50);
    texts[PAUSE].setPosition({240, 275});
    texts[PAUSE].setString("Pause");
    texts[SCORE].setCharacterSize(30);
    texts[SCORE].setPosition({180, 0});
    texts[LIVES].setCharacterSize(30);
    texts[LIVES].setPosition({310, 0});
}

void updateText(sf::Text (&texts)[TEXT_COUNT], Ball& ball)
{
    texts[SCORE].setString("Score: " + std::to_string(ball.score));
    texts[LIVES].setString("Lives: " + std::to_string(ball.live));
}