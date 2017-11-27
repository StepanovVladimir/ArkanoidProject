#include "platform.h"
#include "ball.h"
#include "text.h"
#include <SFML/Graphics.hpp>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 600;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Arkanoid Game Clone", sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow& window, Platform& platform)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            handlePlatformKeyPress(event.key, platform);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            handlePlatformKeyRelease(event.key, platform);
        }
    }
}

void update(sf::Clock& clock, Platform& platform, Ball& ball)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    if (ball.shape.getPosition().y < WINDOW_HEIGHT)
    {
        updatePlatform(platform, elapsedTime);
        updateBall(ball, elapsedTime, platform);
    }
}

void render(sf::RenderWindow& window, Platform& platform, Ball& ball, sf::Text& text)
{
    window.clear();
    window.draw(platform.shape);
    window.draw(ball.shape);
    if (ball.shape.getPosition().y >= WINDOW_HEIGHT)
    {
        window.draw(text);
    }
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    Platform platform;
    Ball ball;
    sf::Font font;
    sf::Text text;
    initializePlatform(platform);
    initializeBall(ball);
    initializeText(font, text);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, platform);
        update(clock, platform, ball);
        render(window, platform, ball, text);
    }

    return 0;
}