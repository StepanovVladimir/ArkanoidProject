#include "platform.h"
#include <SFML/Graphics.hpp>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 600;
constexpr unsigned WINDOW_HEIGHT = 800;
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

void update(sf::Clock& clock, Platform& platform)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    updatePlatform(platform, elapsedTime);
}

void render(sf::RenderWindow& window, const Platform& platform)
{
    window.clear();
    window.draw(platform.shape);
    window.display();
}

int main(int, char* [])
{
    sf::RenderWindow window;
    createWindow(window);

    Platform platform;
    initializePlatform(platform);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, platform);
        update(clock, platform);
        render(window, platform);
    }

    return 0;
}