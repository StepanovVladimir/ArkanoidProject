#include "ball.h"
#include "text.h"

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

void update(sf::Clock& clock, Platform& platform, Ball& ball, std::vector<Block>& blocks)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    if (ball.shape.getPosition().y - ball.shape.getRadius() < WINDOW_HEIGHT)
    {
        updatePlatform(platform, elapsedTime);
        updateBall(ball, elapsedTime, platform, blocks);
    }
}

void render(sf::RenderWindow& window, Platform& platform, Ball& ball,
sf::Text& text, std::vector<Block>& blocks)
{
    window.clear();
    window.draw(platform.shape);
    window.draw(ball.shape);
    if (ball.shape.getPosition().y - ball.shape.getRadius() >= WINDOW_HEIGHT)
    {
        window.draw(text);
    }
    for (auto& block : blocks)
    {
        window.draw(block.shape);
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
    std::vector<Block> blocks;
    initializePlatform(platform);
    initializeBall(ball);
    initializeText(font, text);
    initializeBlocks(blocks);
    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, platform);
        update(clock, platform, ball, blocks);
        render(window, platform, ball, text, blocks);
    }
    return 0;
}